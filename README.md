# About Dupe Buster
Dupe Buster is a small C++ project to delete duplicate messages (SMS or MMS) from a SMS Backup&amp;Restore backup.
It uses Lee Thomason's [TinyXML2](http://www.grinninglizard.com/tinyxml2/) for XML parsing.

For most needs, SMS Backup&amp;Restore is a great Android app. However, it doesn't always deal well with duplicate messages, and deleting them by hand is not always an option.

The goal of Dupe Buster is to provide a minimal-impact solution for deleting duplicates in your file without busting your whole backup.

This project is still a **work in progress**, so please do not expect too much of it :)

## Features
* Identifies duplicates in a SMS Backup&amp;Restore XML backup file and deletes them
* SMS and MMS support

## Potential issues
* Requires duplicates to be positioned one after another in the backup files
* Special characters and emoji support is *unknown*
* Quick and dirty code
* International prefixes not handled (French prefix only, hard-coded)
* TinyXML2's XML auto-formatting when writing may cause issues in MMS in some cases (needs further testing)

# License
Dupe Buster is licensed under **the Unlicense**:

> This is free and unencumbered software released into the public domain.

> Anyone is free to copy, modify, publish, use, compile, sell, or
> distribute this software, either in source code form or as a compiled
> binary, for any purpose, commercial or non-commercial, and by any
> means.

> In jurisdictions that recognize copyright laws, the author or authors
> of this software dedicate any and all copyright interest in the
> software to the public domain. We make this dedication for the benefit
> of the public at large and to the detriment of our heirs and
> successors. We intend this dedication to be an overt act of
> relinquishment in perpetuity of all present and future rights to this
> software under copyright law.

> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
> IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
> OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
> ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
> OTHER DEALINGS IN THE SOFTWARE.

> For more information, please refer to <http://unlicense.org/>

Long story short, you can do anything you want with this small piece of code. Of course, any form of credit would be appreciated, but do not feel obliged to do so :)
