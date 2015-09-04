Rescle(RESource Command Line Editor) is not a resource compiler,
but poweful tool for Windows application developers.

## Purpose ##
  * customize resource without build
    * i.e. for multi-distribution products

## Features ##
You can edit resouces at x86/x64 PE files (EXE/DLL/OCX..).
  * Version Information
  * String Table
  * Manifest
  * Icon
  * Bitmap
  * Cursor
  * Any Binary

## Limitations ##
  * works on windows only
  * command line interface
    * but you can do it to edit update.py
  * cannot change binary same resource id but language is different
  * digital signed PE files is not supported

## Sample ##
Now, you can edit resource from Python script,
but it is not supported from command line.

  * Python code
```
# -*- coding: utf-8 -*-
import sys
import rescle

ru = rescle.ResourceUpdater()

if ru.Load( sys.argv[1] ):
        lang_id = 1033
        
        string_id = 103
        ru.ChangeString( lang_id, string_id, u'your string.' )
        
        ru.ChangeVersionString( lang_id, u'Comments',         u'日本語, Unicode 対応.' )
        ru.ChangeVersionString( lang_id, u'CompanyName',      u'your company.' )
        ru.ChangeVersionString( lang_id, u'FileDescription',  u'your file desc.' )
        ru.ChangeVersionString( lang_id, u'FileVersion',      u'1, 2, 3, 4' )
        ru.ChangeVersionString( lang_id, u'InternalName',     u'your internal name.' )
        ru.ChangeVersionString( lang_id, u'LegalCopyright',   u'your legal copyright.' )
        ru.ChangeVersionString( lang_id, u'LegalTrademarks',  u'your legal trademarks.' )
        ru.ChangeVersionString( lang_id, u'OriginalFilename', u'your original filename.' )
        ru.ChangeVersionString( lang_id, u'PrivateBuild',     u'5, 6, 7, 8' )
        ru.ChangeVersionString( lang_id, u'ProductName',      u'your product name' )
        ru.ChangeVersionString( lang_id, u'ProductVersion',   u'9, 10, 11, 12' )
        ru.ChangeVersionString( lang_id, u'SpecialBuild',     u'13, 14, 15, 16' )
        
        version_id = 1
        ru.ChangeVersionFileVersion( lang_id, version_id, 1, 2, 3, 4 )
        ru.ChangeVersionProductVersion( lang_id, version_id, 9, 10, 11, 12 )
        
        ru.Commit()
```

  * Install from source
```
python setup.py build_ext
python setup.py build
python setup.py install
```

  * Run
```
python update.py your.exe
```