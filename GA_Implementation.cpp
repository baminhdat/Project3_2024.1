#include <bits/stdc++.h>
using namespace std;
int n;
const int popSize = 100;
const int popIter = 100;
const int selectedSize = 30;
int dis[1000][1000];
vector<bool> done;
void input(){
	cin>>n;
	for(int i=0;i<n;i++){
		done.push_back(false);
		for(int j=0;j<n;j++){
			cin>>dis[i][j];
		}
	}
}
class Individual{
	public:
		vector<int> a;
		int fitness;
		void computeFitness(){
			//Fitness la tong do dai duong di, muc tieu minimize fitness
			int temp = 0;
			int cur = 0;
			for(int i=0;i<n;i++){
				temp+= dis[cur][a[i]];
				cur = a[i];
			}
			temp += dis[cur][0];
			fitness = temp;
		}
		Individual(){
			for(int i=0;i<n-1;i++){
				a.push_back(i+1);
			}
			random_shuffle(a.begin(),a.end());
			computeFitness();
		}
		Individual(Individual i1, Individual i2){
			a.resize(n-1);
			//Crossover
			int temp1 = rand()%(n-1);
			int temp2 = rand()%(n-1);
			if(temp1>temp2){
				int tmp = temp2;
				temp2 = temp1;
				temp1 = tmp;
			}
			for(int i=temp1;i<temp2+1;i++){
				a[i] = i1.a[i];
				done[a[i]] = true;
			}
			int cur = temp2+1;
			int run = temp2+1;
			while(cur!=n-1){
				if(run%(n-1)==0){
					run = 0;	
				}
				while(done[i2.a[run]]){
					run++;
				}
				a[cur] = i2.a[run];
				done[a[cur]]=true;
				cur++;
			}
			cur=0;
			while(cur!=temp1){
				if(run%(n-1)==0){
					run = 0;	
				}
				while(done[i2.a[run]]){
					run++;
				}
				a[cur] = i2.a[run];
				done[a[cur]]=true;
				cur++;
			}
		}	
};
vector<Individual> population;
vector<Individual> selected;
void sortAccFitness(){
	sort(population.begin(),population.end(),[](Individual i1, Individual i2){
		return i1.fitness<i2.fitness;
	});
}
void generate(){
	for(int i=0;i<popSize;i++){
		Individual *indi = new Individual();
		population.push_back(*indi);
	}
	sortAccFitness();
}
void select(){
	selected.clear();
	for(int i=0;i<selectedSize;i++){
		int temp1 = rand()%popSize;
		int temp2 = rand()%popSize;
		if(population[temp1].fitness<population[temp2].fitness){
			selected.push_back(population[temp1]);
		}
		else selected.push_back(population[temp2]);
	}
}
int main(){
	input();
	generate();
	int best = population[0].fitness;
	for(int i=0;i<popIter;i++){
		select();
		population.clear();
		for(int j=0;j<popSize;j++){
			int temp1 = rand()%selectedSize;
			int temp2 = rand()%selectedSize;
			Individual *indi = new Individual(selected[temp1],selected[temp2]);
			population.push_back(*indi);
		}
		sortAccFitness();	
		if(best<population[0].fitness){
			best = population[0].fitness;
		}
	}
	cout<<best;
}
