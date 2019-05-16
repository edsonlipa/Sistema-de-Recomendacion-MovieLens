#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

unordered_map<string,unordered_map<string,float> > map_rating;
map<string,map<string,float> > matrix_desviations;
//unordered_map<string,unordered_map<string,float> > matrix_desviations;

//map<string,map<string,float> > map_rating;
//map<float, string> map_knn; // mantenerlo ordenado, los mayores primero
//map<float, string> map_proyeccion;
//map<string,pair<float,float> > map_recomendacion;

string path ="../../";
//string path ="ml-latest/";

vector<string> vec_user;
map<string, string> map_name_movies;


void load_info_names(){

	ifstream archivo_entrada(path+"movies.csv");
    string linea;
    char delim = ',';
    getline(archivo_entrada, linea);
    string cons1;
    string cons2;
    string cons3;
    int maxi = 0;
    int cont = 0;
    while(getline(archivo_entrada, linea)) {
        stringstream ss(linea);

    	getline(ss,cons1,delim);
    	getline(ss,cons2,delim);
		map_name_movies[cons1] = cons2;

    }
    archivo_entrada.close();
}

void load_info(){

	//ifstream archivo_entrada("Movie_Ratings_ to_load.csv");
	ifstream archivo_entrada(path+"MR_load.csv");
    string linea;
    char delim = ',';
    getline(archivo_entrada, linea);
    string cons1;
    string cons2;
    string cons3;
    int maxi = 0;
    int cont = 0;
    while(getline(archivo_entrada, linea)) {
        stringstream ss(linea);

    	getline(ss,cons1,delim);
    	getline(ss,cons2,delim);
    	getline(ss,cons3,delim);
    	if(map_rating.find(cons1) == map_rating.end() ) vec_user.push_back(cons1);
		map_rating[cons1][cons2] = atof(cons3.c_str() );

    }
    archivo_entrada.close();
}
/*
void k_nn(string name, int opt){

	float val_dist;

	float sum_x = 0.0;
    float sum_y = 0.0;
    float prod_xy = 0.0;
    float sum_pot_x = 0.0;
    float sum_pot_y = 0.0;
    float n = 0.0;
    float salida = 0.0;
    float auxi;
    if(opt > 0){
		# pragma omp parallel for private(sum_x,sum_y,prod_xy, sum_pot_x, sum_pot_y, n, salida,auxi)
		//for(it = map_rating.begin();it!=map_rating.end(); it++){
		for(int i = 0; i< vec_user.size(); i++){
    	
			if(vec_user[i] != name){

				map<string, float>::iterator itt =  map_rating[vec_user[i]].begin();
				while(itt != map_rating[vec_user[i]].end() ){

					if( map_rating[name].find(itt->first) != map_rating[name].end() ){
						
	                    prod_xy += pow(abs(itt->second - map_rating[name][itt->first]) , opt) ;

					}
					itt++;
				}
				
				salida = pow(prod_xy, pow(opt,-1));
				//map_knn[it->first] = salida;
				map_knn[salida] = vec_user[i];				
			}
			//it++;
		}
    }

	if(opt == -1){//pearson

		map<string, map<string, float> >::iterator it;
		//while(it != map_rating.end() ){

		# pragma omp parallel for private(sum_x,sum_y,prod_xy, sum_pot_x, sum_pot_y, n, salida,auxi)
		//for(it = map_rating.begin();it!=map_rating.end(); it++){
		for(int i = 0; i< vec_user.size(); i++){
			sum_x = 0.0;
		    sum_y = 0.0;
		    prod_xy = 0.0;
		    sum_pot_x = 0.0;
		    sum_pot_y = 0.0;
		    n = 0.0;
		    salida = 0.0;
			//if(it->first != name){
		    if(vec_user[i] != name){
				//cout<<"RARO  "<<it->first<<endl;

		    	map<string, float>::iterator itt = map_rating.find(vec_user[i])->second.begin();
				//map<string, float>::iterator itt = (it->second).begin();
				//while(itt != it->second.end() ){
		    	while(itt != map_rating.find(vec_user[i])->second.end() ){
					//cout<<"Second  "<<itt->first<<" -> "<<itt->second<<endl;
					if( map_rating[name].find(itt->first) != map_rating[name].end() ){
						//cout<<"HOLA"<<endl;
						//cout<<itt->first<<" -> "<<itt->second<<endl;
                        prod_xy += (float)itt->second * (float)map_rating[name][itt->first] ;
                        //cout<<itt->second<<" ** "<<map_rating[name][itt->first]<<endl;
                        sum_x += itt->second;
                        sum_y += map_rating[name][itt->first];
                        //sum_pot_x += pow( itt->second,2);
                        sum_pot_x += itt->second * itt->second ;
                        //sum_pot_y += pow( map_rating[name][itt->first]  ,2);
                        sum_pot_y += map_rating[name][itt->first]  * map_rating[name][itt->first] ;
                        n++;



					}
					itt++;
				}


				if(n>0){
					auxi = (sqrt( sum_pot_x - pow(sum_x,2)/n )) * (sqrt( sum_pot_y - pow(sum_y,2)/n ));
					//cout<<" auxi  "<<auxi<<endl;
					if(auxi>0.0){//divicion entre 0 error
						salida = (prod_xy - (sum_x*sum_y)/n ) / auxi;
						//map_knn[it->first] = salida;
						//cout<<salida<<"  "<<it->first<<"  err "<<( sqrt( sum_pot_x - pow(sum_x,2)/n ) * sqrt( sum_pot_y - pow(sum_y,2)/n ) )<<endl;
						map_knn[salida] = vec_user[i];
						
					}	
				}
				
				//cout<<salida<<"  val "<<endl;
				
			}


			//it++;
		}


			
	}

	else if(opt == -2){

		# pragma omp parallel for private(sum_x,sum_y,prod_xy, sum_pot_x, sum_pot_y, n, salida,auxi)
		//for(it = map_rating.begin();it!=map_rating.end(); it++){
		for(int i = 0; i< vec_user.size(); i++){

			sum_x = 0.0;
		    sum_y = 0.0;
		    prod_xy = 0.0;
		    sum_pot_x = 0.0;
		    sum_pot_y = 0.0;
		    n = 0.0;
		    salida = 0.0;
			if(vec_user[i] != name){

				map<string, float>::iterator itt = map_rating.find(vec_user[i])->second.begin();
				while(itt != map_rating.find(vec_user[i])->second.end() ){
				//while(itt != it->second.end() ){

					if( map_rating[name].find(itt->first) != map_rating[name].end() ){
						//cout<<"HOLA"<<endl;
						//cout<<cons1<<" -> "<<cons2<<endl;
                        prod_xy += itt->second * map_rating[name][itt->first] ;
                        //sum_x += itt->second;
                        //sum_y += map_rating[name][itt->first];
                        sum_pot_x += pow( itt->second,2);
                        sum_pot_y += pow( map_rating[name][itt->first]  ,2);
                        
					}
					else{
						//prod_xy += itt->second * map_rating[name][itt->first] ;
                        //sum_x += itt->second;
                        //sum_y += map_rating[name][itt->first];
                        sum_pot_x += pow( itt->second,2);
                        //sum_pot_y += pow( map_rating[name][itt->first]  ,2);
                        
					}

					itt++;
				}
				map<string, float>:: iterator ite = map_rating[name].begin();
				while(ite != map_rating[name].end() ){ // revisar EXAMPLEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe
					if(map_rating[vec_user[i]].find(ite->first)   == map_rating[vec_user[i]].end() ){
						sum_pot_y += pow( ite->second  ,2);
					}
					ite++;
				}


				//cout<<prod_xy<<" - "<<sum_x<<" - "<<sum_y<<" - "<<sum_pot_x<<" - "<<sum_pot_y<<" - "<<n<<endl;
				//n--;
				//salida = (prod_xy - (sum_x*sum_y)/n ) / ( sqrt( sum_pot_x - pow(sum_x,2)/n ) * sqrt( sum_pot_y - pow(sum_y,2)/n ) );
				if(sum_pot_y>0 && sum_pot_x>0){  //divicion en 0   0/0 == error
					salida = prod_xy /  (sqrt(sum_pot_x) * sqrt( sum_pot_y ) );
					//cout<<"SAL  "<<salida<<endl;
					//map_knn[it->first] = salida;	
					//map_knn[salida] = it->first;
					map_knn[salida] = vec_user[i];
				}
				
			}


			//it++;
		}


			
	}

	
}


void print_knn(int k,int opt){
	cout<<"KNNN"<<endl;
	if(opt>0){
		map<float, string>::iterator it = map_knn.begin();
		while(it != map_knn.end() && k--){
			cout<<it->first<<"  -  "<<it->second<<endl;
			it++;
		}
		cout<<map_knn.size()<<endl;	
	}

	else{

		//map<string, float>::iterator it = map_knn.begin();
		map<float, string>::reverse_iterator it = map_knn.rbegin();
		while(it != map_knn.rend() && k--){
			cout<<it->first<<"  --  "<<it->second<<endl;
			it++;
		}
		cout<<map_knn.size()<<endl;
	}
}

void proyeccion(string book_name, int k, int opt){
	cout<<"PROYECCION : "<<endl;

	float sum_dis = 0.0;
	float val_proyeccion = 0.0;
	

	map<float, string>::reverse_iterator it = map_knn.rbegin();
	while(it != map_knn.rend() ){
		if(map_rating[it->second].find(book_name) != map_rating[it->second].end() ){
			map_proyeccion[it->first] = it->second;
			sum_dis += it->first;
			k--;
			//cout<<it->first<<" "<<it->second<<endl;
		} 
		it++;
	}
	map<float,string>::reverse_iterator itt = map_proyeccion.rbegin();
	//cout<<sum_dis<<endl;
	
	while(itt != map_proyeccion.rend() ){
		val_proyeccion += (itt->first / sum_dis ) * map_rating[itt->second][book_name];
		//cout<<itt->first / sum_dis<<"  *  "<<map_rating[itt->second][book_name]<<endl;
		itt++;
	}
	cout<<"Para: "<<book_name<<" : "<<val_proyeccion<<endl;
}

void recomendacion(string name,int kk){
	int k = kk;
	string temp_book = "";
	float temp_rating;
	cout<<"RECOM : knn size:  "<<map_knn.size()<<endl;
	map<float, string>::reverse_iterator it = map_knn.rbegin();
	while(it != map_knn.rend() && k )
	{
		temp_rating = 0.0;
		map<string, float >::iterator itt = map_rating[it->second].begin();
		//if(it->second == "\"25131\"") cout<<"HERE"<<it->second<<endl;
		while(itt != map_rating[it->second].end() ){
			//cout<<"Rating  "<<itt->first<<"   "<<itt->second<<endl;
			if(map_rating[name].find(itt->first) == map_rating[name].end() ){

				//cout<<"Rating2  "<<itt->first<<"   "<<itt->second<<endl;
				
				if(temp_rating < itt->second ){
					temp_book = itt->first;
					temp_rating = itt->second;
				}
				
			}
			itt++;
		}

		//cout<<"LIBRO: "<<temp_book<<"   Punt "<<temp_rating<<endl;
		if(map_recomendacion.find(temp_book) == map_recomendacion.end() ){
			map_recomendacion[temp_book] = make_pair(temp_rating,1.0);
			k--;
		}
		else{
			map_recomendacion[temp_book].first += temp_rating;
			map_recomendacion[temp_book].second++;

		}

		it++;
		
	}

	k = kk;
	multimap<float, string> aux_recomend;
	float auxx;
	map<string , pair<float, float> >::iterator iter = map_recomendacion.begin();
	while(iter != map_recomendacion.end() ){
		auxx = iter->second.first / iter->second.second;
		//aux_recomend[auxx] = iter->first; 
		aux_recomend.insert(pair<float,string>(auxx, iter->first));
		//iter->second.first = iter->second.first / iter->second.second;
		iter++;
	}
	//cout<<"TAM "<<aux_recomend.size()<<endl;

	cout<<"RECOMENDACION "<<aux_recomend.size()<<" tam "<<endl;
	//map<float, string>::reverse_iterator r_it = aux_recomend.rbegin();
	multimap<float, string>::reverse_iterator r_it = aux_recomend.rbegin();
	//cout<<r_it->second<<" punt "<<r_it->first<<endl;
//	while(r_it != aux_recomend.rend() && k--){
	while(r_it != aux_recomend.rend() ){

		//cout<<r_it->second<<" punt "<<r_it->first<<endl;
		cout<<map_name_movies[r_it->second]<<" punt "<<r_it->first<<endl;
		r_it++;
	}

}
*/
float get_variance (string item1,string item2)
{
	if(item1==item2)return 0;
	float numerator=0;
	float card=0;
	for (auto temp_1:map_rating[item1])
	{
		unordered_map<string,float>::iterator found= map_rating[item2].find(temp_1.first);
		if(found!=map_rating[item2].end()){
			numerator+=temp_1.second-found->second;
			card++;
		}
	}
	cout<<"the variance "<<item1+" "+item2<<" "<<numerator/card<<endl;
	return numerator/card;	
}
void set_iter(unordered_map<string,unordered_map<string,float>>::iterator &it,
				int step,
				unordered_map<string,unordered_map<string,float>> u_m)
{
	it=u_m.begin();
	advance(it,step);
}
void update_matrix_variance(){
	auto fit_i =begin(map_rating);
	int total_items = map_rating.size();
	//# pragma omp parallel for private (fit_i)  
	for(int i=1; i<total_items; i++)
	{
		auto fit_j =begin(map_rating);
		set_iter(fit_j,i,map_rating);
		for (int j = i; j < total_items; j++)
		{	float this_variance = get_variance(fit_i->first,fit_j->first);
			matrix_desviations[fit_i->first][fit_j->first]=this_variance;
			matrix_desviations[fit_j->first][fit_i->first]=-this_variance;
			set_iter(fit_j,j,map_rating);
		}
		set_iter(fit_i,i,map_rating);
	}
	
}
int main()
{
	auto start = std::chrono::system_clock::now();

	//load_info();
	map_rating ={
		{"Taylor",{{"Amy",4},{"Ben",5},{"Daisy",5}}},
		{"PSY",{{"Amy",3},{"Ben",2},{"Clara",3.5}}},
		{"Whitney",{{"Amy",4},{"Clara",4},{"Daisy",3}}}

	};
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "la carga de datos a tardado: " << elapsed_seconds.count() << "s\n";
	string name = "26891";
	
	update_matrix_variance();

	cout<<"size "<<map_rating.size()<<endl;
	for(auto i:matrix_desviations){
		for(auto j:i.second){
			cout<<i.first<<" "<<j.first<<" "<<j.second<<endl;
		}
	}
	cout<<"matrix size "<<matrix_desviations.size()<<endl;

/*
	
	int opt = -2;  // -1 -> pearson   |  -2-> coseno
	int k = 4;
	int k2;
	cout<<"START: "<<endl;
	while(getline(cin,name)){
	
		if (name.empty()) continue;
	    istringstream is(name);
	
		map_knn.clear();
		map_recomendacion.clear();
		map_proyeccion.clear();
		cout<<name<<endl;
		cout<<"option: ";
		cin>>opt;	cout<<opt<<endl;
		cout<<" K : ";
		cin>>k;
		cout<<k<<endl;
		cout<<"Recomendacion: ";
		cin>>k2;	cout<<k2<<endl;

		start = std::chrono::system_clock::now();

		k_nn(name,opt);
		//cout<<map_knn.size()<<endl;
		print_knn(k,opt);
		//proyeccion(bookn,k,opt);
		recomendacion(name,k2);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::cout<< "la consulta a tardado: " << elapsed_seconds.count() << "s\n";
				
		cout<<"TAM: "<<map_recomendacion.size()<<endl;

		cout<<"***************************"<<endl;
	}
*/
        return 1;
}
