#include <iostream>
#include<string.h>
#include<fstream>
using namespace std;
ifstream f("Arbore AVL.txt");

struct nod_arbAVL
{
    int val, balance;
     struct nod_arbAVL *left, *right;


};

void rotatie_stg(struct nod_arbAVL *&a)
{
    struct nod_arbAVL *aux=a->right;
    a->right=aux->left;
    aux->left=a;
    a->balance=a->balance-(1+max(aux->balance,0));
    aux->balance=aux->balance-(1-min(a->balance,0));
    a=aux;

}


void rotatie_drp (struct nod_arbAVL *&a)
{
    struct nod_arbAVL *aux=a->left;
    a->left=aux->right;
    aux->right=a;
    a->balance=a->balance+(1-min(aux->balance,0));
    aux->balance=aux->balance+(1+max(a->balance,0));
    a=aux;

}

void rotatie_stg_drp(struct nod_arbAVL *&a)
{
   rotatie_stg(a->left);
   rotatie_drp(a);

}

void rotatie_drp_stg(struct nod_arbAVL *&a)
{
   rotatie_drp(a->right);
   rotatie_stg(a);

}

void echilibreaza (struct nod_arbAVL *&a)
{
    if(a->balance==-2)
        if(a->left->balance==-1)
           rotatie_drp(a);
          else
            rotatie_stg_drp(a);
      else
    if(a->balance==2)
        if(a->right->balance==1)
           rotatie_stg(a);
          else
            rotatie_drp_stg(a);
}



int inser (struct nod_arbAVL *&a, int x)
{
    if(a==NULL)
    {  a=new nod_arbAVL;
       a->val=x;
       a->balance=0;
       a->left=a->right=NULL;
       return 1;
    }
    else
    {
        if(a->val==x)
        {
            cout<<"Elementul "<<x<<" exista deja in arbore\n";
            return 0;
        }
        if(x>a->val)
            if(inser(a->right,x)==1)
              a->balance++;
             else
              return 0;
           else
            if(inser(a->left,x)==1)
              a->balance--;
             else
              return 0;
    }

      if(a->balance==-1||a->balance==1||a->balance==0)
        return 1;
       else
       {   cout<<"Echilibrare\n";
           echilibreaza(a);
           return 0;

       }


}


void cautare(struct nod_arbAVL *a,int x)
{
    while(a!=NULL&&a->val!=x)
       if(x>a->val)
         a=a->right;
       else
         a=a->left;

    if(a!=NULL)
        cout<<"Elementul a fost gasit in arbore\n";
    else
        cout<<"Elementul nu a fost gasit in arbore\n";
}


void maxim(struct nod_arbAVL *a)
{
    while(a->right!=NULL)
        a=a->right;

    cout<<"Cel mai mare elem din arbore este: "<<a->val<<"\n";

}

void afisare_srd ( struct nod_arbAVL *a)
{
    if(a!=NULL)
    {

        afisare_srd(a->left);
        cout<<a->val<<" ";
        afisare_srd(a->right);
    }
}

void afisare_rsd ( struct nod_arbAVL *a)
{
    if(a!=NULL)
    {
        cout<<a->val<<" ";
        afisare_rsd(a->left);

        afisare_rsd(a->right);
    }
}




void sterge(struct nod_arbAVL *&a,int x )
{
    struct nod_arbAVL *b=a, *aux, *c=a;

cout<<"Stergem elementul "<<x<<" din arbore\n";
   while(a!=NULL&&x!=a->val)
    if(x<a->val)
       a=a->left;
     else
       a=a->right;


       if(a==NULL)
          { cout<<"Valoarea nu se afla in arbore\n"; a=c; }
       else
       {  int ok=1;

          while((b->left!=NULL||b->right!=NULL)&&ok)
         { if(b->left!=NULL&&b->right!=NULL)
           {
             if(b->left->val!=x&&b->right->val!=x)
              if(x<b->val)
                b=b->left;
               else
                b=b->right;
              else
                ok=0;
           }
           else
        {
         if(b->left!=NULL)
            if(b->left->val!=x)
                b=b->left;
             else
                ok=0;
           else
           if(b->right!=NULL)
            if(b->right->val!=x)
                b=b->right;
             else
                ok=0;
           }
         }



         if( a->right==NULL&&a->left==NULL )
         {
           if(b->left!=NULL&&b->left->val==x)
             b->left=NULL;
             else
             b->right=NULL;

             delete a;
              a=c;
                    }
           else
         {
          if(a->left==NULL)
          {
              aux=a;
               if(b->left!=NULL&&b->left->val==x)
                b->left=a->right;         ///mai trebuie niste conditii pentru null la drp sau stg lui b
               else
                if(b->right!=NULL)
                b->right=a->right;
               delete aux;

          }

           if(a->right==NULL)
          {
              aux=a;
               if(b->left!=NULL&&b->left->val==x)
                b->left=a->left;
               else
                if(b->right!=NULL)
                b->right=a->left;
               delete aux;

          }

         }

         if( a->right!=NULL&&a->left!=NULL )
         {
             while(a->right->right!=NULL)
                   { a->val=a->right->val;
                     a->right->val=x;
                     a=a->right;
                     }

                  a->val=a->right->val;
                  a->right->val=x;
                  aux=a->right;
                  a->right=NULL;
                 delete aux;


         }
        a=c;
         cout<<"Valoare stearsa\n";

      }



}


int main()
{   int x;
    char s[41];
    struct nod_arbAVL *a=NULL;  /// a<=> radacina

    while(!f.eof())
    {
         f.getline(s,40);

         if(strcmp(s,"inser")==0)
         {
             f>>x;
             cout<<"Se introduce elem: "<<x<<"\n";
             inser(a,x);
         }
         else
          if(strcmp(s,"cautare")==0)
         {
             f>>x;
             cout<<"Se cauta elem: "<<x<<"\n";
             cautare(a,x);
         }
         else
          if(strcmp(s,"maxim")==0)
         {
             maxim(a);
         }
         else
          if(strcmp(s,"afisare_crescatoare")==0)
         {
             cout<<"Afisare SRD arbore binar de cautare<=>sir sortat: ";
             afisare_srd(a);
             cout<<"\n";
              afisare_rsd(a);
             cout<<"\n";
         }
         else
          if(strcmp(s,"sterge")==0)
         {
             f>>x;
             sterge(a,x);
         }



    }
    return 0;
}
