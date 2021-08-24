@ECHO OFF
mode con cols=140 lines=70

rmdir /s /q build

mkdir old_dist
move dist\* old_dist\

C:\Python\Python36-32\scripts\pip install wheel twine --upgrade
C:\Python\Python37-32\scripts\pip install wheel twine --upgrade
C:\Python\Python38-32\scripts\pip install wheel twine --upgrade
C:\Python\Python39-32\scripts\pip install wheel twine --upgrade

C:\Python\Python36-64\scripts\pip install wheel twine --upgrade
C:\Python\Python37-64\scripts\pip install wheel twine --upgrade
C:\Python\Python38-64\scripts\pip install wheel twine --upgrade
C:\Python\Python39-64\scripts\pip install wheel twine --upgrade

C:\Python\Python36-32\python setup.py sdist bdist_wheel
C:\Python\Python37-32\python setup.py sdist bdist_wheel
C:\Python\Python38-32\python setup.py sdist bdist_wheel
C:\Python\Python39-32\python setup.py sdist bdist_wheel

C:\Python\Python36-64\python setup.py sdist bdist_wheel
C:\Python\Python37-64\python setup.py sdist bdist_wheel
C:\Python\Python38-64\python setup.py sdist bdist_wheel
C:\Python\Python39-64\python setup.py sdist bdist_wheel

REM C:\Python\Python37-32\scripts\twine upload dist/* -r pypitest
