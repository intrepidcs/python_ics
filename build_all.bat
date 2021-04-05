@ECHO OFF
mode con cols=140 lines=70

rmdir /s /q build

mkdir old_dist
move dist\* old_dist\

C:\Python36-32\scripts\pip install wheel twine --upgrade
C:\Python37-32\scripts\pip install wheel twine --upgrade
C:\Python38-32\scripts\pip install wheel twine --upgrade

C:\Python36-64\scripts\pip install wheel twine --upgrade
C:\Python37-64\scripts\pip install wheel twine --upgrade
C:\Python38-64\scripts\pip install wheel twine --upgrade

C:\Python36-32\python setup.py sdist bdist_wheel
C:\Python37-32\python setup.py sdist bdist_wheel
C:\Python38-32\python setup.py sdist bdist_wheel

C:\Python36-64\python setup.py sdist bdist_wheel
C:\Python37-64\python setup.py sdist bdist_wheel
C:\Python38-64\python setup.py sdist bdist_wheel

REM C:\Python34\scripts\twine upload dist/* -r pypitest
