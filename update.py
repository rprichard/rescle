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