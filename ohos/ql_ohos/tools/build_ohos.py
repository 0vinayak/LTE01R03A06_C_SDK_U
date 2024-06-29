#!/usr/bin/env python3
# Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
# All rights reserved.
#
# This software is supplied "AS IS" without any warranties.
# RDA assumes no responsibility or liability for the use of the software,
# conveys no license or title under any patent, copyright, or mask work
# right to the product. RDA reserves the right to make changes in the
# software without notification.  RDA also make no representation or
# warranty that such application will be suitable for the specified use
# without further testing or modification.

import argparse
import sys
import io
import os
import shutil
import json
import xml.etree.ElementTree as ET
import glob
from pathlib import Path
import tarfile

DESCRIPTION = """
Compile ohos.
"""

DESCRIPTION_COPYFILE = """
Create deliver pack from XML description.
"""

"""
devliver.xml format

For each XML file, there are:
* source base directory: all sources are related to
* destination base directory: all destination are related to
Usually, both of them are None. Which means that source are related to
current directory, and destination are related to the root of output.

All sources should be related to source base directory, and destination
can be related to root of output by set root="y".

The root element tag of XML should be 'deliver'.

When the element supports 'inclusive' and 'exclusive', the condition is:
* Neither 'inclusive' nor 'exclusive' appear, the element should be taken;
* When there are no valid 'inclusive', it won't be taken;
* When there are valid 'exclusive', it won't be taken;

The element types:

* Devliver a file.

    <file src="src" dst="dst" dstdir="dir" root="y" optional="y"
        inclusive="tag,tag" exclusive="tag,tag"/>

  Unless optional="y", the source file must exist.

  The destination order:
  * When "dst" exist, it will be used. Otherwise,
  * When "dstdir" exist, the destination file will be under "dstdir", and
    the file name is the same as source. Otherwise,
  * The directory and file name is the same as source.

* Deliver glob of files.

    <globfile src="*.h" dstdir="dst" root="y"
        inclusive="tag,tag" exclusive="tag,tag"/>

  It is not an error when glob of file is empty. Also, the matched
  directory will be ignored.

  When "dstdir" doesn't exist, the destination directory will be the same
  as source.

* Deliver a directory.

    <recursive src="src" dst="dst" root="y" optional="y"
        exclude="name,name" inclusive="tag,tag" exclusive="tag,tag"/>

  When "dst" doesn't exist, the destination directory will be the same
  as source.

* Handle sub-directory (not implemented now)

    <subdir dir="dir" dst="dst" xml="xml" root="y" optional="y"
        inclusive="tag,tag" exclusive="tag,tag"/>

  By default, both source base directory and destination directory will be
  changed to "dir" sub-directory. When "dst" exist, the destination
  directory will be changed to "dst" sub-directory.

  The default XML in sub-directory is "deliver.xml".

* Include another xml. The working directory won't be changed.

    <include xml="xml" optional="y"
        inclusive="tag,tag" exclusive="tag,tag"/>

* Group with the same conditions.

    <group inclusive="tag,tag" exclusive="tag,tag">
        <file .../>
        <globfile .../>
        <recursive .../>
        <subdir .../>
        <include .../>
        <group .../>
    </group>
"""


class Deliver(object):

    def __init__(self, itags, etags, kwords, src_base, dst_base):
        self.src_base = src_base
        self.dst_base = dst_base
        self.itags = itags
        self.etags = etags
        self.kwords = kwords
        self.flist = {}

    def loadxml(self, fname):
        with open(fname, 'r') as fh:
            fdata = fh.read()

        root = ET.fromstring(fdata.format(**self.kwords))
        if root.tag != 'deliver':
            raise Exception('invalid deliver xml')

        for elem in list(root):
            self._load_elem(elem)

    def _load_elem(self, elem):
        if not self._check_tags(elem):
            return

        if elem.tag == 'file':
            self._load_file(elem)
        elif elem.tag == 'globfile':
            self._load_globfile(elem)
        elif elem.tag == 'recursive':
            self._load_recursive(elem)
        elif elem.tag == 'subdir':
            self._load_subdir(elem)
        elif elem.tag == 'include':
            self._load_include(elem)
        elif elem.tag == 'group':
            self._load_group(elem)
#        elif elem.tag == 'copydir':
#            self._load_copydir(elem)
        else:
            raise Exception('invalid deliver xml tag' + elem.tag)

    def _add_file(self, src, dst):
        if dst in self.flist and src != self.flist[dst]:
            raise Exception('conflict ' + dst)

        self.flist[dst] = src

    def _check_tags(self, elem):
        itags = []
        etags = []
        if elem.get('inclusive'):
            itags = elem.get('inclusive').split(',')
        if elem.get('exclusive'):
            etags = elem.get('exclusive').split(',')

        if not itags and not etags:
            return True

        checked = False
        if self.itags:
            for tag in itags:
                if tag in self.itags:
                    checked = True
                    break

        if not checked:
            return False

        if self.etags:
            for tag in etags:
                if tag in self.etags:
                    return False

        return True

    def _load_group(self, elem):
        for subelem in list(elem):
            self._load_elem(subelem)

    def _build_dst(self, dst, dstroot):
        if dstroot or not self.dst_base:
            return dst

        return self.dst_base + '/' + dst

    def _build_src(self, src):
        if not self.src_base:
            return src

        return self.src_base + '/' + src

    def _load_file(self, elem):
        optional = elem.get('optional', 'n') == 'y'
        dstroot = elem.get('root', 'n') == 'y'

        src = elem.get('src')
        if src is None:
            raise Exception('src is missed in file element')

        src = os.path.normpath(src.replace('\\', '/'))

        if elem.get('dst'):
            dst = self._build_dst(elem.get('dst'), dstroot)
        elif elem.get('dstdir'):
            dst = self._build_dst(elem.get('dstdir'),
                                  dstroot) + '/' + Path(src).name
        else:
            dst = self._build_dst(src, False)

        src = self._build_src(src)
        if not optional and not os.path.exists(src):
            raise Exception(src + ' doesn\'t exist')

        self._add_file(src, dst)

    def _load_globfile(self, elem):
        src = elem.get('src')
        if src is None:
            raise Exception('src is missed in globfile element')

        src = os.path.normpath(src.replace('\\', '/'))
        dstroot = elem.get('root', 'n') == 'y'

        if elem.get('dstdir'):
            dstdir = self._build_dst(elem.get('dstdir'), dstroot)
        else:
            dstdir = self._build_dst(str(Path(src).parent), False)

        src = self._build_src(src)
        srcdir = str(Path(src).parent)
        for fname in glob.glob(src):
            name = Path(fname).name
            srcfname = srcdir + '/' + name
            dstfname = dstdir + '/' + name
            if not os.path.isfile(srcfname):
                continue

            self._add_file(srcfname, dstfname)

    def _load_recursive(self, elem):
        excludes = []
        if elem.get('exclude'):
            excludes = elem.get('exclude').split(',')

        src = elem.get('src')
        if src is None:
            raise Exception('src is missed in recursive element')

        src = os.path.normpath(src.replace('\\', '/'))
        dstroot = elem.get('root', 'n') == 'y'

        if elem.get('dst'):
            dst = self._build_dst(elem.get('dst'), dstroot)
        else:
            dst = self._build_dst(src, False)

        src = self._build_src(src)
        self._load_recursive_dir(src, dst, excludes)

    def _load_recursive_dir(self, src, dst, excludes):
        for child in os.listdir(src):
            if excludes and child in excludes:
                continue

            srcname = src + '/' + child
            dstname = dst + '/' + child
            if os.path.isfile(srcname):
                self._add_file(srcname, dstname)
            elif os.path.isdir(srcname):
                self._load_recursive_dir(srcname, dstname, excludes)

    def _load_subdir(self, elem):
        pass

    def _load_include(self, elem):
        src = elem.get("xml")
        if src is None:
            raise Exception('xml is missed in include element')

        fname = self._build_src(src)
        optional = elem.get('optional', 'n') == 'y'
        if not optional and not os.path.exists(fname):
            raise Exception(fname + ' doesn\'t exist')

        deliver = Deliver(self.itags, self.etags, self.kwords)
        deliver.src_base = self.src_base
        deliver.dst_base = self.dst_base
        deliver.loadxml(fname)

        for dst, src in deliver.flist.items():
            self._add_file(src, dst)

    def _load_copydir(self, elem):
        src = elem.get('src')
        if src is None:
            raise Exception('src is missed in copydir element')

        src = os.path.normpath(src.replace('\\', '/'))
        dstroot = elem.get('root', 'n') == 'y'

        if elem.get('dstdir'):
            dstdir = self._build_dst(elem.get('dstdir'), dstroot)
        else:
            dstdir = self._build_dst(str(Path(src).parent), False)

        src = self._build_src(src)
        srcdir = str(Path(src).parent)
        shutil.copytree(srcdir, dstdir)


def load_args(sub_parsers):
    parser = sub_parsers.add_parser('load',
                                    help='load description xml to json')
    parser.set_defaults(func=load)
    parser.add_argument('--inclusive', dest="inclusive", nargs="*",
                        help="inclusive tags")
    parser.add_argument('--exclusive', dest="exclusive", nargs="*",
                        help="exclusive tags")
    parser.add_argument('--keyword', dest='keyword', nargs='*',
                        help='keyword used in description')
    parser.add_argument('--src_base', dest='src_base',
                        help='src base')
    parser.add_argument('--dst_base', dest='dst_base',
                        help='dst base')
    parser.add_argument('xml', help='description XML file')
    parser.add_argument('output', help='output json file')


def load(args):
    kwords = {}
    if args.keyword:
        for elem in args.keyword:
            k, v = elem.split('=')
            kwords[k] = v
#            print(k,v)

    deliver = Deliver(args.inclusive, args.exclusive, kwords, args.src_base, args.dst_base)
    deliver.loadxml(args.xml)
    with open(args.output, 'w') as fh:
        json.dump(deliver.flist, fh, sort_keys=True, indent=4)

def pack_args(sub_parsers):
    parser = sub_parsers.add_parser('pack',
                                    help='pack to jamie_pack based on file list json')
    parser.set_defaults(func=pack)
    parser.add_argument('--output', dest='output', default='jamie_output_pack',
                        help='output pack dir name')
    parser.add_argument('json', nargs='+', help='file list json')

def pack(args):
    flist = {}
    
    for fname in args.json:
        with open(fname, 'r') as fh:
            fl = json.loads(fh.read())

        if not fl:
            continue

        for dst, src in fl.items():
            if dst in flist and src != flist[dst]:
                raise Exception('conflict ' + dst)
            flist[dst] = src
    
    for dst in sorted(flist.keys()):
        dst_file=dst
        if not os.path.exists(os.path.dirname(dst_file)):
            os.makedirs(os.path.dirname(dst_file))
        shutil.copyfile(flist[dst], dst_file)


def ohos_args(sub_parsers):
    parser = sub_parsers.add_parser('ohos_args', help='about dir')
    parser.set_defaults(func=get_ohos_args)
    parser.add_argument('--ohos_top_dir', dest="ohos_top_dir", help="openharmony top directory")
    parser.add_argument('--board_name', dest="board_name", help="board name")
    parser.add_argument('--product_name', dest="product_name", help="product name")

def get_ohos_args(args):
    print("--ohos_top_dir ", args.ohos_top_dir)
    print("--board_name ", args.board_name)
    print("--product_name ", args.product_name)
    return args

def test_args(sub_parsers):
    parser = sub_parsers.add_parser('test',
                                    help='test func')
    parser.set_defaults(func=test)
    parser.add_argument('--quec', dest="quec", help="quec test")

def test(args):
    print("test quec str:"+args.quec)

def ql_pack(argv):
    parser = argparse.ArgumentParser(description=DESCRIPTION_COPYFILE)
    sub_parsers = parser.add_subparsers(help="sub-commands")

    test_args(sub_parsers)
    load_args(sub_parsers)
    pack_args(sub_parsers)

    args = parser.parse_args(argv)
    if args.__contains__('func'):
        return args.func(args)

    parser.parse_args(['-h'])
    return 0

def ql_ohos_args(argv):
    parser = argparse.ArgumentParser(description=DESCRIPTION_COPYFILE)
    sub_parsers = parser.add_subparsers(help="sub-commands")

    ohos_args(sub_parsers)

    args = parser.parse_args(argv)
    if args.__contains__('func'):
        return args.func(args)

    parser.parse_args(['-h'])
    return 0

def ql_change_xml_name(xml_path, board_name, product_name):
    # [TODO]need to do
    print("jamie: xml xml_path", xml_path)
    print("jamie: xml board_name", board_name)
    print("jamie: xml product_name", product_name)
    # 修改实体的定义
    ET.entity['board_name'] = board_name
    ET.entity['product_name'] = product_name

    # 解析 XML 文件
    tree = ET.parse(xml_path)
    root = tree.getroot()

    # 将修改后的 ElementTree 对象重新写入到 XML 文件中
    tree.write(xml_path)

def main(argv):

    script_path = os.path.abspath(__file__)
    current_dir = os.path.dirname(script_path)
    quec_top_dir = os.path.abspath(current_dir + '/../../../')
    ohos_top_dir = os.path.abspath(current_dir + '/../../')
    # quec_top_dir = 'E:/p4_pro/depot3/unisoc/8910/dev/R02/'
    # ohos_top_dir = 'E:/p4_pro/depot3/unisoc/8910/temp/Jamie/openharmony_3_0/'

    # ohos dir
    if(len(sys.argv) >= 3):
        ohos_args = ql_ohos_args(argv)
        if(ohos_args.ohos_top_dir):
            ohos_top_dir = ohos_args.ohos_top_dir

    if quec_top_dir[-1] == '\\' or quec_top_dir[-1] == '/':
        quec_top_dir = quec_top_dir[:-1]
    if ohos_top_dir[-1] == '\\' or ohos_top_dir[-1] == '/':
        ohos_top_dir = ohos_top_dir[:-1]
    
    xml_path = quec_top_dir+'/'+'ohos/ql_ohos/tools/core_filelist_ohos.xml'
    json_path = quec_top_dir+'/'+'ohos/ql_ohos/tools/ohos_list.json'

    ohos_inc_path = quec_top_dir + '/' + 'ohos/ql_ohos/ohos_inc'
    ohos_libs_path = quec_top_dir + '/' + 'ohos/ql_ohos/ohos_libs'

    print("quec_top_dir:", quec_top_dir)
    print("ohos_top_dir:", ohos_top_dir)

    if not os.path.exists(ohos_inc_path):
        # 如果不存在，则创建该文件夹
        os.makedirs(ohos_inc_path)
    else:
        # 清除
        shutil.rmtree(ohos_inc_path)

    if not os.path.exists(ohos_libs_path):
        # 如果不存在，则创建该文件夹
        os.makedirs(ohos_libs_path)
    else:
        # 清除
        shutil.rmtree(ohos_libs_path)

    board_name = ''
    product_name = ''
    if(len(sys.argv) >= 8):
        ohos_args = ql_ohos_args(argv)
        if(ohos_args.board_name):
            board_name = ohos_args.board_name
        if(ohos_args.product_name):
            product_name = ohos_args.product_name
    # if(board_name or product_name):
    #     ql_change_xml_name(xml_path, board_name, product_name)
   
    # ql_pack(['test', '--quec', 'hhh'])
    ql_pack(['load', '--src_base', ohos_top_dir, '--dst_base', quec_top_dir + '/ohos/ql_ohos', '--', xml_path, json_path])
    ql_pack(['pack', '--', quec_top_dir+'/'+'ohos/ql_ohos/tools/ohos_list.json'])
    return 0


def main1(argv):
    ohos_src_dir = os.getcwd()+"/ohos/out/ecx00u/ql_unisoc/libs"
    ohos_dest_dir = os.getcwd()+"/components/quectel/ql_open/ql_api/ohos/ohos_libs"

    print("ohos lib src dir:"+ohos_src_dir)
    print("ohos lib dst dir:"+ohos_dest_dir)

    shutil.rmtree(ohos_dest_dir)
    shutil.copytree(ohos_src_dir, ohos_dest_dir)

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
