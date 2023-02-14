#include <stdlib.h>
template <class T>
class vector {
    private:
        T *v;
        int s;
    public:
        vector(){
	        s=0;
	        v=NULL;
        }
	  
        vector(vector<T> &v)
        {
            this->size = v.size;
            this->arr = new T[v.size];
            for(int i = 0; i < v.size; i++){
                this->arr[i] = v.arr[i];
            }
            //vector <int> size(other.size);
            //vector<int> other(v);

            //for(int i = 0; i < other.size(); ++i){
            //   cout << other[i] << endl;
            //}

        }
        ~vector(){
	        delete [] v;
        }
	    vector(const vector &v);

        int size() {
	        return s;
        }
	  
        void push_back(T ele) {
	        T *temp;
	        temp = new T[++s];
	        for(int i=0; i<s-1; i++)
	            temp[i]=v[i];

	        delete [] v;
	        v=temp;
	        v[s-1]=ele;
        }
};
