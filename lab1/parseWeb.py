#!/usr/bin/env python
import sys
import re


class webEntry:
  """Class for storing web entries"""
  def __init__ (self,page,frm,date):
     """Initialize a webEntry object with pagename, computer from,  date accessed"""
     self.page=page;
     self.frm=frm;
     self.date=date;


  def printIt(self):
     print "Page:%s from=%s date=%s"%(self.page,self.frm,self.date)


def buildTree(logFile):
  """Opens a logfile and buids a list containg all page entries
   
     logFile -file to read"""

  try:
    f=open(logFile)
  except:
    print "Try to open %s"%logFile    
    sys.exit(-1)
  parse=re.compile("^(\S+) - - \[(.+)\] \"GET (\S+)") 
  
  array=[]
  for line in f.readlines():
    x=parse.search(line)
    if x:
       array.append(webEntry(x.group(3),x.group(1),x.group(2)))
  return array
   

  


def  parseArgs():
  """"httpdSearch logFile searchTerm"""
  if len(sys.argv)!=3:
        print "httpdSearch logFile searchTerm";
     	sys.exit(-1);
  logFile=sys.argv[1];
  searchTerm=sys.argv[2]   
  return logFile,searchTerm


def searchList(database,searchTerm):
  """Search database for searchTerm and print it out"""

  myRegEx=re.compile(searchTerm)
  for item in database:
    if myRegEx.search(item.page):
	item.printIt()



logF,mySearch=parseArgs()
myList=buildTree(logF)
searchList(myList,mySearch)
