DEVLIB  = ./dpf-ax
DPFLIB = $(DEVLIB)/dpflib

all: pydpflib_c dpflib python

pydpflib_c:
	if test -d dpf-ax; \
	then echo dpf-ax already downloaded; \
	else svn co -r6 https://dpf-ax.svn.sourceforge.net/svnroot/dpf-ax/trunk dpf-ax; \
	fi	
	

dpflib:
	$(MAKE) -C $(DPFLIB) all

python:
	python setup.py build


clean:
	$(MAKE) -C $(DPFLIB) clean
	python setup.py clean --all
	
install:
	python setup.py install
