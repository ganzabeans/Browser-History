// Anisha Braganza
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>     // std::next, std::prev

#include "Page.h"       // struct to hold page info

using std::string;

class BrowserHistory {
  public:
    BrowserHistory();

    void visitSite(string url, size_t filesize);
    void backButton();
    void forwardButton();

    void readFile(string fileName);

    string currentUrl();
    size_t currentPageSize();
    size_t getHistoryLength();
  private:
    std::list<Page> history_;  //DLL
    std::list<Page>::iterator itr_;  //Iterator

    // string temps
    string tempURL_, tempCommand_;
    size_t tempPgSize_;

 // back clicked bool for deleting history 
    bool moveB = false;
};

BrowserHistory::BrowserHistory() {
  itr_ = history_.begin();
}

  // Reads a file and stores it in list
  void BrowserHistory::readFile(string fileName){

  //open and read file
  std::ifstream myfile;
  myfile.open(fileName);

  while (myfile >> tempCommand_){
    // fill history to Page
    if (tempCommand_.compare("visit") == 0){
      myfile >> tempURL_ >> tempPgSize_;
      visitSite(tempURL_, tempPgSize_);
    }
    if (tempCommand_.compare("back") == 0) backButton();
    if (tempCommand_.compare("forward") == 0) forwardButton();
  }
  myfile.close();
}

void BrowserHistory::visitSite(string url, size_t filesize){
  // deletes forward history
  if (moveB) {
    history_.erase(history_.begin(), itr_);
    itr_ = history_.begin();
  }
  history_.insert(itr_, Page(url, filesize));
  --itr_;
  }

void BrowserHistory::backButton(){
  itr_++;
  if (itr_ == history_.end())
    itr_--;
  if (!moveB) moveB = true;
}

void BrowserHistory::forwardButton(){
  if (itr_ != history_.begin())
    itr_--;
  }

string BrowserHistory::currentUrl(){
  if (history_.empty()) return "";
  return (*itr_).url;
}

size_t BrowserHistory::currentPageSize(){
    if (history_.empty()) return 0;
    return (*itr_).f_sz;
}
size_t BrowserHistory::getHistoryLength(){
  return history_.size();
}