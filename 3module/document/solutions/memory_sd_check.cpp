/*
  Problem: memory
  Author: Andrew Stankevich
  Solution by: Semyon Dyatlov
  Correct, uses a heap and a list
  Checks the input
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define for if (0) ; else for

#define MINN 1
#define MAXN 2147483647
#define MINM 1
#define MAXM 100000

//#define DEBUG
#ifdef DEBUG
#define debug_printf printf
#else
#define debug_printf gobble
#endif

void Assert(bool b)
{
  if (!b)
  {
    fprintf(stderr,"BAD INPUT\n");
    exit(1);    
  }
}

inline void gobble(const char*, ...)
{
}

struct Segment
{
  Segment *prev, *next;
  bool free;
  int l, r, p;

  Segment(Segment *prev, Segment *next, bool free, int l, int r, int p);

  void remove();
};

int n, m, k, l, rs[MAXM];
Segment *h[MAXM], *r[MAXM];
/* rs=request status: 0=declined, 1=allocated, 2=removed */

Segment::Segment(Segment *prev, Segment *next, bool free, int l, int r, int p)
{
  this->prev = prev;
  this->next = next;
  this->free = free;
  this->l = l;
  this->r = r;
  this->p = p;
  if (prev)
    prev->next = this;
  if (next)
    next->prev = this;
}

void Segment::remove()
{
  if (prev)
   prev->next = next;
  if (next)
    next->prev = prev;
}

void swap(int a, int b)
{
  Segment *t = h[a];
  h[a] = h[b];
  h[b] = t;
  h[a]->p = a;
  h[b]->p = b;
}

bool better(int a, int b)
{
  return h[a]->r-h[a]->l>h[b]->r-h[b]->l;
}

void heapify(int a)
{
  for (;;)
  {
    int q = a;
    if (((a<<1)+1<l)&&better((a<<1)+1,q))
      q = (a<<1)+1;
    if (((a<<1)+2<l)&&better((a<<1)+2,q))
      q = (a<<1)+2;
    if (a==q)
      return;
    swap(a,q);
    a = q;
  }
}

void heap_remove()
{
  --l;
  if (l)
  {
    swap(0,l);
    heapify(0);
  }
}

void heap_lift(int a)
{
  while (a&&better(a,(a-1)>>1))
  {
    swap(a,(a-1)>>1);
    a = (a-1)>>1;
  }
}

void heap_remove(int a)
{
  swap(a,l-1);
  --l;
  if (a>=l)
    return;
  heap_lift(a);
  heapify(a);
}

void heap_add(Segment *a)
{
  a->p = l;
  h[l] = a;
  heap_lift(l++);
}

void allocate(int a)
{
  Assert((1<=a)&&(a<=n));
  debug_printf("allocate: a=%d\n",a);
  Segment *c = h[0];
  if (!l||(c->r-c->l<a)) //allocation impossible
  {
    rs[k++] = 0;
    printf("-1\n");
    return;
  }
  rs[k++] = 1;
  r[k-1] = new Segment(c->prev,c,false,c->l,c->l+a,-1);
  debug_printf("allocated from (%d,%d) a portion (%d,%d)\n",c->l,c->r,r[k-1]->l,r[k-1]->r);
  printf("%d\n",1+c->l);
  c->l += a;
  if (c->l<c->r) //decrease the key
    heapify(c->p);
  else //remove the segment
  {
    debug_printf("removed (%d,%d)\n",c->l,c->r);
    c->remove();
    heap_remove();
    delete c;
  }
}

void remove(int a)
{
  --a;
  if (!((0<=a)&&(a<k)&&(rs[a]!=2)))
    a = a;
  Assert((0<=a)&&(a<k)&&(rs[a]!=2));
  rs[k++] = 2;
  if (!rs[a])
    return;
  rs[a] = 2;
  Segment *c = r[a], *sp = c->prev, *sn = c->next;
  bool bp = sp&&sp->free;
  bool bn = sn&&sn->free;
  debug_printf("remove: a=%d bp=%d bn=%d: ",a+1,(int) bp,(int) bn);
  if (!bp&&!bn) //create a new segment
  {
    debug_printf("case 1: created segment (%d,%d)\n",c->l,c->r);
    c->free = true;
    heap_add(c);
    return;
  }
  if (!bp) //enlarge the next segment
  {
    debug_printf("case 2: enlarged segment from (%d,%d) to (%d,%d)\n",sn->l,sn->r,c->l,sn->r);
    sn->l = c->l;
    heap_lift(sn->p);
    c->remove();
    delete c;
    return;
  }
  if (!bn) //enlarge the previous segment
  {
    debug_printf("case 3: enlarged segment from (%d,%d) to (%d,%d)\n",sp->l,sp->r,sp->l,c->r);
    sp->r = c->r;
    heap_lift(sp->p);
    c->remove();
    delete c;
    return;
  }
  debug_printf("case 4:merged (%d,%d) and (%d,%d)\n",sp->l,sp->r,sn->l,sn->r);
  sp->r = sn->r;
  heap_lift(sp->p);
  c->remove();
  delete c;
  heap_remove(sn->p);
  sn->remove();
  delete sn;
}

int main()
{
  freopen("memory.in","rt",stdin);
  freopen("memory.out","wt",stdout);

  Assert((scanf("%d%d",&n,&m)==2)&&(MINN<=n)&&(n<=MAXN)&&(MINM<=m)&&(m<=MAXM));
  l = 1;
  h[0] = new Segment(0,0,true,0,n,0);
  for (int i=0;i<m;i++)
  {
    int t;
    Assert(scanf("%d",&t)==1);
/*    if (i<=800)
    {
      Segment *z = h[0]; 
      while (z->prev)
        z = z->prev;
      while (z)
      {
        fprintf(stderr,"%d %d\n",z->l,z->r);
        z = z->next;
      }
      fprintf(stderr,"---: %d\n",i+1);
    }*/
    if (t>0)
      allocate(t);
    else
      remove(-t);
  }
  
  return 0;
}