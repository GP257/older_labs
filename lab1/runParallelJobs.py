#!/usr/bin/env python
import sys
import subprocess
import os
import time

class job:
  """A generalized class for describing a parallel job"""
  def __init__(self,tag):
    """Initizlize a job"""
    self.tag=tag;
  def preJob(self):
     """How to prepare a job to be run"""
     #By default we don't need to do anything
  def checkJobFinishedCorrectly(self):
     """A routine to see if a job finished correctly"""
     return True;
        
  def returnJobCommand(self):
     """Return a string containing how to run the job,stdout,stderr"""
  def postJob(self):
     """Stuff I need to do after a job has run"""
     
class runParallelJob:
  """A generalized base class for running a series ob jobs in parallel"""
  def __init__(self,tags):
     """Initialization of the base class
        tags is a dictionary with a tag->job """
     self.tags=tags
     self.jobsRunning={}
     self.failed={}

  def startJob(self,key,str):
    """How to start a job"""
    #Needs to be overwritten
    sys.exit(-1) #Force to be overwritten
  
  def checkJobsRunning(self):
    """Check to see what jobs are running """ 
    #Force this to be overwritten
    print "checkJobsRunning must be overwritten"
    sys.exit(-1)  
    
  def checkJobsFinished(self,finished): 
     """Check to see if the jobs finished correctly"""
     for job in finished:
       if not self.jobsRunning[job].checkJobFinishedCorrectly():
           #check to see if the job failed before
           if self.failed.count(job)==0:
              self.failed[job]=0;
           #update the count of failed job
           self.failed[job]+=1
           #if the jobs has filed more than twice give up on it
           if self.failed[job] >2:
              print "Giving up on %s"%job
           #try to run tj job again
           else:
              self.tags[job]=self.jobsRunning[job]
       del self.jobsRunning[job]
     
      
  def allJobsFinished(self):
     """What to do when all the jobs are finished"""

  def runJobs(self,sleepTime,maxJobsRunning):
     """Run a series of parallel jobs"""
     while len(self.tags) >0 or len(self.jobsRunning) >0:
       jobsFinished=self.checkJobsRunning()
       self.checkJobsFinished(jobsFinished)
       if len(self.jobsRunning) < maxJobsRunning  and len(self.tags)>0:
         key,job=self.tags.popitem()
         print "starting job ",key
         self.jobsRunning[key]=job;
         c,o,e=job.returnJobCommand()
         self.startJob(key,c,o,e)
       time.sleep(sleepTime)
     self.allJobsFinished();


class singleNodeParallel(runParallelJob):
  """Run many jobs simultansously on a single node"""
  def __init__(self,tags):
    runParallelJob.__init__(self,tags)
    self.processPoll={}
  def startJob(self,key,command,stdo,stde):
    if stde:
      if stdo:
         efile=open(stde,"w");
         ofile=open(stdo,"w");
         self.processPoll[key]=subprocess.Popen(command,stderr=efile,stdout=ofile,shell=True)
      else:
         efile=open(stde,"w");
         self.processPoll[key]=subprocess.Popen(command,stderr=efile,shell=True)
    else:
      if stdo:
         ofile=open(stdo,"w");
         self.processPoll[key]=subprocess.Popen(command,stdout=ofile,shell=True)
      else:
         self.processPoll[key]=subprocess.Popen(command,shell=True)
  def checkJobsRunning(self):
    finished=[]
    for job,p in self.processPoll.items():
       if p.poll() is not None:
          finished.append(job)
          del self.processPoll[job] 
    return finished    
    
class piCalc(job):
  def __init__(self,tag):
    job.__init__(self,tag);
  def returnJobCommand(self):
	return "./piCalc.x  %d"%self.tag,"/tmp/%s.%d"%(os.environ["USER"],self.tag),None
	
class piParallel(singleNodeParallel):
  def __init__(self,njobs):
    jobs={}
    self.nc=njobs;
    for i in range(njobs):
       jobs[i]=piCalc(i)
    singleNodeParallel.__init__(self,jobs)

  def allJobsFinished(self):
    tot=[]
    for i in range(self.nc):
       f=open("/tmp/%s.%d"%(os.environ["USER"],i))
       lines=f.readlines()
       tot.append(float(lines[0].strip()))
    sum=0.
    for v in tot:
       sum+=v
    print sum/self.nc
    

x=piParallel(20)
x.runJobs(.5,5)
  

     
