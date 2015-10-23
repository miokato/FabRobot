
class MeanFilter {
  private:
    int index;
    int buflen;
    int buf[];


  public:
    MeanFilter();
    int meanFilter(int row);
};
