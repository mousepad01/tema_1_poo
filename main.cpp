#include <iostream>
using namespace std;

struct nod_vecin{

    int valoare;

    nod_vecin *next;
};

class nod{

    int valoare;

    nod_vecin *first;
    nod_vecin *last;

    public:

    nod(){

        first = NULL;
        last = NULL;

    }

    int get_val(){

        return this -> valoare;
    }

    nod_vecin *get_list_first(){

        return first;
    }

    nod_vecin *get_list_last(){

        return last;
    }

    void update_val(int k){

        this -> valoare = k;
    }

    void add(int k);

    void print();

};

class graf_neorientat{

    int n;

    nod *noduri = NULL;

    public:

    graf_neorientat();

    graf_neorientat(const graf_neorientat &old);

    ~graf_neorientat(){

        delete []noduri;
    }

    int get_n(){

        return n;
    }

    void set_n(int k);

    nod *get_vecini(){

        return noduri;
    }

    void update_graf(int x, int y);

    void update_graf_unidir(int x, int y);

    void add_nod(int k);

    friend ostream & operator<<(ostream &out, const graf_neorientat&obj);

    friend istream & operator>>(istream &in, graf_neorientat &g);

    graf_neorientat * citire(int k);

    void afisare(int ng, graf_neorientat *v);

    void DFS(int k, int *vizitat);

    int * BFS(int k);

    int ** matricea_drumurilor();

    int ** comp_conexe();

    int check_conex();

    graf_neorientat operator +(const graf_neorientat& graf_de_adunat){

        graf_neorientat grez;
        grez.set_n(n);

        for(int i = 1; i <= n; i++){

            nod_vecin *aux = graf_de_adunat.noduri[i].get_list_first();

            while(aux != NULL){

                nod_vecin *aux2 = this -> noduri[i].get_list_first();

                int t = 0;
                while(aux2 != NULL){

                    if(aux2 -> valoare == aux -> valoare)
                        t = 1;

                    aux2 = aux2 -> next;
                }

                if(t == 0){

                    grez.update_graf_unidir(i, aux -> valoare);
                }

                aux = aux -> next;
            }
        }

        for(int i = 1; i <= n; i++){

            nod_vecin *aux = noduri[i].get_list_first();

            while(aux != NULL){

                grez.update_graf_unidir(i, aux -> valoare);

                aux = aux -> next;
            }
        }

        return grez;
    }

};

void nod::add(int k){

        nod_vecin *to_add = new nod_vecin;

        to_add -> valoare = k;
        to_add -> next = NULL;

        if (this -> first == NULL){

            first = to_add;
            last = to_add;
        }
        else{

            last -> next = to_add;
            last = to_add;
        }
    }

void nod::print(){

        nod_vecin *aux = this -> first;

        while (aux != NULL){

            cout<<aux -> valoare<<" ";
            aux = aux -> next;
        }

        cout<<'\n';
    }


graf_neorientat::graf_neorientat(){

        n = 0;
}

graf_neorientat::graf_neorientat(const graf_neorientat &old){

        n = old.n;

        noduri = new nod[n + 1];

        for (int i = 1; i <= n; i ++){

            noduri[i].update_val(i);
        }

        for(int i = 1; i <= n;i ++){

            nod_vecin *aux = old.noduri[i].get_list_first();
            while (aux != NULL){

                noduri[i].add(aux -> valoare);
                aux = aux -> next;
            }
        }

    }

 void graf_neorientat::set_n(int k){

        n = k;

        noduri = new nod[n + 1];

        for (int i = 1; i <= n; i ++){

            noduri[i].update_val(i);
        }
    }

void graf_neorientat::update_graf(int x, int y){

        if(x > n)
            add_nod(x);

        if(y > n)
            add_nod(y);

        noduri[x].add(y);
        noduri[y].add(x);

    }

void graf_neorientat::update_graf_unidir(int x, int y){

        if(x > n)
            add_nod(x);

        if(y > n)
            add_nod(y);

        noduri[x].add(y);

}

void graf_neorientat::add_nod(int k){

    nod* newArr = new nod[n + 2];
    std::copy(noduri, noduri + std::min(n + 1, n + 2), newArr);
    delete[] noduri;
    noduri = newArr;

    noduri[k].update_val(k);
    this -> n = n + 1;

}

ostream & operator<<(ostream &out, const graf_neorientat&obj){

        for (int i = 1;i <= obj.n; i++){

            out<<"nod "<<i<<" cu vecinii: ";
            obj.noduri[i].print();
        }
        out<<'\n';

        int **ma = new int*[obj.n + 1];
        for(int i = 0; i <= obj.n; i++)
            ma[i] = new int[obj.n + 1];

        for (int i =1; i <= obj.n; i ++)
            for(int j = 1; j <= obj.n; j++)
                ma[i][j] = 0;

        for(int i = 1; i <= obj.n; i++){

            nod_vecin *aux = obj.noduri[i].get_list_first();

            while (aux != NULL){

                ma[obj.noduri[i].get_val()][aux -> valoare] = 1;

                aux = aux -> next;
            }
        }

        for(int i = 1; i <= obj.n; i++){
            for(int j = 1; j <= obj.n; j++)
                out<<ma[i][j]<<" ";
            out<<'\n';
        }
        out<<'\n';

        for (int i = 0; i <= obj.n; i++)
            delete []ma[i];
        delete []ma;

         for(int i = 1; i <= obj.n; i++){

            nod_vecin *aux = obj.noduri[i].get_list_first();

            while (aux != NULL){

                out<<obj.noduri[i].get_val()<<" "<<aux -> valoare<<'\n';

                aux = aux -> next;
            }
        }
        out<<'\n';
    }

istream & operator>>(istream &in, graf_neorientat &g){

    int n;
    in>>n;
    g.set_n(n);

    int m;
    in>>m;

    for(int i =1; i <= m; i++ ){

        int n1, n2;
        in>>n1>>n2;
        g.update_graf(n1, n2);
    }

}

graf_neorientat * graf_neorientat::citire(int ng){

    graf_neorientat *grafuri = new graf_neorientat[ng + 1];


    for(int k = 1; k <= ng; k ++){

        cin>>grafuri[k];
    }

    return grafuri;
}

void graf_neorientat::afisare(int ng, graf_neorientat *v){

    for(int i = 1; i <= ng; i++){

        cout<<v[i]<<'\n'<<'\n';
    }
}

void graf_neorientat::DFS(int k,int *vizitat){

        vizitat[k] = 1;

        nod_vecin *aux = noduri[k].get_list_first();

        while (aux != NULL){

            if (!vizitat[aux -> valoare])
                DFS(aux -> valoare, vizitat);

            aux = aux -> next;
        }
    }

int * graf_neorientat::BFS(int k){

        int *vizitat = new int[n + 1];
        for(int i = 1; i <= n; i ++)
            vizitat[i] = 0;

        int *coada = new int[n + 1];

        int st, dr;

        st = dr = 0;
        coada[st] = k;

        while(st <= dr){

            nod_vecin *aux = noduri[coada[st]].get_list_first();

            while(aux != NULL){

                if (!vizitat[aux -> valoare]){

                    vizitat[aux -> valoare] = 1;
                    dr++;
                    coada[dr] = aux -> valoare;
                }

                aux = aux -> next;
            }
            st++;
        }
        return vizitat;
    }

int ** graf_neorientat::matricea_drumurilor(){

        int **md = new int*[n + 1];
        for(int i = 0; i <= n; i++)
            md[i] = new int[n + 1];

        for (int i =1; i <= n; i ++)
            for(int j = 1; j <= n; j++)
                md[i][j] = 0;

        for(int i = 1; i <= n; i++){

            nod_vecin *aux = noduri[i].get_list_first();

            while (aux != NULL){

                md[noduri[i].get_val()][aux -> valoare] = 1;

                aux = aux -> next;
            }
        }

        for(int k = 1 ; k <= n ; ++k)
            for(int i = 1 ; i <= n ; ++i)
                for(int j = 1 ; j <= n ; ++j)
                    if( i != j && md[i][j] == 0 &&  md[i][k] == 1 && md[k][j] == 1)
                        md[i][j] = 1;

        return md;
    }

int ** graf_neorientat::comp_conexe(){

        int *vizitat = new int[n + 1];
        for(int i = 0;i <= n; i++)
            vizitat[i] = 0;

        int t = 0;
        int **mv = new int*[n + 1];
        for(int i = 0; i <= n; i++)
            mv[i] = NULL;

        for(int i = 1; i <= n; i++)

            if(!vizitat[i]){

                vizitat[i] = 1;

                t ++;
                mv[t] = new int[n + 1];
                for(int j = 0; j <= n; j++)
                    mv[t][j] = 0;

                DFS(i, mv[t]);

                for(int j = 1; j <= n; j++)
                    if(mv[t][j])
                        vizitat[j] = 1;
            }
        return mv;

    }

int graf_neorientat::check_conex(){

        int **mv = new int*[n + 1];
        mv = comp_conexe();

        if(mv[2] == NULL)
            return 1;
        else
            return 0;
    }

int main(){

    int ng;
    cin>>ng;
    graf_neorientat *v = v  -> citire(ng);

    v -> afisare(ng, v);

    graf_neorientat g(v[1]);

    int n = g.get_n();

    cout<<g;

    graf_neorientat g2(g);

    cout<<g2;

    g2.update_graf(n, n + 1); /// exemplu de modificare in graf pentru a crea alt graf diferit; se adauga muchie de la nodul n la un nod nou urmator n + 1

    cout<<g2;

    int *vizitat = new int[n + 1];
    for(int i =1; i <= n; i ++)
        vizitat[i] = 0;
    g.DFS(1, vizitat);
    for(int i = 1; i <= n; i++)
        cout<<vizitat[i]<<" ";
    cout<<'\n';

    int *viz = g.BFS(5);
    for(int i = 1; i <= n; i++)
        cout<<viz[i]<<" ";
    cout<<'\n'<<'\n';

    int **md;
    md = g.matricea_drumurilor();
    for(int i =1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout<<md[i][j]<<" ";
        cout<<'\n';
    }
    cout<<'\n';

    int **mv;
    mv = g.comp_conexe();
    for(int i =1; i <= n && mv[i] != NULL; i++){
        for(int j = 1; j <= n; j++)
            cout<<mv[i][j]<<" ";
        cout<<'\n';
    }
    cout<<'\n';

    if(g.check_conex())
        cout<<"este conex";
    else
        cout<<"nu este conex";

    cout<<'\n'<<'\n';

    ///graf_neorientat grez(n);
    graf_neorientat g3(g);
    g3.update_graf(1, n);

    graf_neorientat g4(g);
    g4.update_graf(n - 1, n);

    graf_neorientat grez = g3 + g4;
    cout<<grez;

    return 0;
}
