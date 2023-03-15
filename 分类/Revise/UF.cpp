class UF{
private:
	vector<int> id, size;
public:
	UF(int n) : size(n , 1) {
		iota(id.begin(), id.end(), 0); //<numric>
	}
	
	int find(int p) {
		while(p != id[p]) {
			id[p] = id[id[p]];
			p = id[p];
		}
		return p;
	}
	
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}
	
	void connect(int p, int q) {
		int i = find(p), j = find(q);
        if(i != j){
            /*秩压缩*/
            if(size[i] < size[j]){
                id[i] = j;
                size[j] += size[i];
            }
            else{
                id[j] = i;
                size[i] += size[j];
            }
        }
	}
};