## Instructions for new updates

1. Update the version number:
	increase the version field in pyproject.toml (for example, 0.1.1 → 0.1.2)

2. Compile the C library:
	
	```
	cd ~/Turkish-Syllable
	gcc -shared -fPIC -o turkish_syllable/libsyllable.so turkish_syllable/syllable.c -Iinclude
	```

3. Do local test:

	```
	python3 local_test.py
	```

4. Clean the /dist/ and wheelhouse/ folders (don't mix old files):

	```
	rm -rf dist/* wheelhouse/*
	```

5. Create the package:
	
	```
	python3 -m build
	```

6. Ensure Manylinux Compatibility:

	```
	auditwheel repair dist/turkish_syllable-0.1.2-cp310-cp310-linux_x86_64.whl
	```

7. Test in TestPyPI:

	```
	twine upload --repository testpypi wheelhouse/turkish_syllable-0.1.2-cp310-cp310-manylinux_*.whl dist/turkish_syllable-0.1.2.tar.gz
	```

8. Testing library:

	```
	python3 -m venv test_env
	source test_env/bin/activate
	pip install --index-url https://test.pypi.org/simple/ --no-cache-dir turkish-syllable
	python -c "from turkish_syllable import syllabify; print(syllabify('Merhaba, dünya!'))"
	python -c "from turkish_syllable import syllabify; print(syllabify('Merhaba, dünya!', with_punctuation=False))"
	deactivate
	```

9. If everything is OK in TestPyPI, upload the image to PyPI:

	```
	twine upload wheelhouse/turkish_syllable-0.1.2-cp310-cp310-manylinux_*.whl dist/turkish_syllable-0.1.2.tar.gz
	```

10. Testing:
	
	```
	python3 -m venv test_env2
	source test_env2/bin/activate
	pip install turkish-syllable
	pip show turkish-syllable  # Version: 0.1.2 olmalı
	python -c "from turkish_syllable import syllabify; print(syllabify('Merhaba, dünya!'))"
	deactivate
	```