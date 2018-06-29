@ECHO OFF
mode con cols=140 lines=70


C:\Python27\scripts\pip install wheel twine
C:\Python33\scripts\pip install wheel twine
C:\Python34\scripts\pip install wheel twine
C:\Python35\scripts\pip install wheel twine
C:\Python36-32\scripts\pip install wheel twine
C:\Python37-32\scripts\pip install wheel twine

C:\Python27-64\scripts\pip install wheel twine
C:\Python34-64\scripts\pip install wheel twine
C:\Python35-64\scripts\pip install wheel twine
C:\Python36-64\scripts\pip install wheel twine
C:\Python37-64\scripts\pip install wheel twine

C:\Python27\python setup.py sdist bdist_wheel
C:\Python33\python setup.py sdist bdist_wheel
C:\Python34\python setup.py sdist bdist_wheel
C:\Python35\python setup.py sdist bdist_wheel
C:\Python36-32\python setup.py sdist bdist_wheel
C:\Python37-32\python setup.py sdist bdist_wheel


C:\Python27-64\python setup.py sdist bdist_wheel
C:\Python34-64\python setup.py sdist bdist_wheel
C:\Python35-64\python setup.py sdist bdist_wheel
C:\Python36-64\python setup.py sdist bdist_wheel
C:\Python37-64\python setup.py sdist bdist_wheel

C:\Python34\scripts\twine upload dist/* -r pypitest
