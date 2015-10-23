#include "MeanFilter.h"

MeanFilter::MeanFilter(){
  index = 0;
  buflen = 5;
}




int MeanFilter::meanFilter(int row) {
  buf[index] = row;
  index = (index + 1) % buflen;

  long sum = 0;
  for (int i=0; i < buflen; i++){
    sum += buf[i];
  }

  return (int)(sum / buflen);
}

