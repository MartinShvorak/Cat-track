#include <SFML/Graphics.hpp>
#include<cmath>
using namespace sf;
const int nom=8;
struct Сatcar
{
    int poi[nom][2] = {300, 610,1270,430,1380,2380};
    float x,y,tempo,control; int n;
    Сatcar() {tempo=2; control=0; n=0;}
    void supervision()
     {
      x += sin(control) * tempo;
      y -= cos(control) * tempo;
     }
    void object()
  {
    float temx=poi[n][0];
    float temy=poi[n][1];
    float beta = control-atan2(temx-x,-temy+y);
    if (sin(beta)<0) control+=0.005*tempo;
    else control-=0.005*tempo;
    if ((x-temx)*(x-temx)+(y-temy)*(y-temy)<625) n=(n+1)%nom;
   }
};
int main()
{
    RenderWindow win (VideoMode(640,480),"Meny game");

        Texture meytext,btex1,btex2,btex3;
        meytext.loadFromFile("E:/proba/Carmape/images/meny.png");
        meytext.setSmooth(true);
        Sprite sprite1(meytext);
        RectangleShape but1(Vector2f(100,35));
        but1.setFillColor(Color(50,50,50));
        but1.setPosition(120,100);
        RectangleShape but2(Vector2f(100,35));
        but2.setFillColor(Color(50,50,50));
        but2.setPosition(120,200);
        RectangleShape but3(Vector2f(100,35));
        but3.setFillColor(Color(50,50,50));
        but3.setPosition(120,300);
        while (win.isOpen()){
            Vector2i mousepoz = Mouse::getPosition(win);
            Event ev;
            while(win.pollEvent(ev)){
                if(ev.type ==sf::Event::Closed)
                    win.close();

                if(ev.type == Event::MouseButtonPressed)
                    if(ev.key.code == Mouse::Left)
                        if(but1.getGlobalBounds().contains(mousepoz.x,mousepoz.y)){
                            but1.setFillColor(Color(255,0,0));
                            RenderWindow app(VideoMode(640, 480), "Map1");
                                app.setFramerateLimit(60);
                                Texture texture1,texture2;
                                texture1.loadFromFile("E:/proba/Carmape/images/map1.png");
                                texture2.loadFromFile("E:/proba/Carmape/images/Catcat.png");
                                texture1.setSmooth(true);
                                texture2.setSmooth(true);
                                Sprite sBackground(texture1), sCat(texture2);
                                sBackground.scale(2,2);
                                sCat.setOrigin(22, 22);
                                float R=22;
                                const int N=5;
                                Сatcar Сatcar[N];
                                for(int i=0;i<N;i++)
                                {
                                  Сatcar[i].x=300+i*50;
                                  Сatcar[i].y=1700+i*80;
                                  Сatcar[i].tempo=7+i;
                                }
                               float s=0,a=0;
                               float maxs=12.0;
                               float acc=0.2, dec=0.3;
                               float turns=0.08;
                               int ox=0,oy=0;
                                while (app.isOpen())
                                {
                                    Event e;
                                    while (app.pollEvent(e))
                                    {
                                        if (e.type == Event::Closed)
                                            app.close();
                                    }
                                bool u=0,r=0,d=0,l=0;
                                if (Keyboard::isKeyPressed(Keyboard::W)) u=1;
                                if (Keyboard::isKeyPressed(Keyboard::D)) r=1;
                                if (Keyboard::isKeyPressed(Keyboard::S)) d=1;
                                if (Keyboard::isKeyPressed(Keyboard::A)) l=1;
                                if (u && s<maxs){
                                    if (s < 0)  s += dec;
                                    else  s += acc;
                                }
                                if (d && s>-maxs){
                                    if (s > 0) s -= dec;
                                    else  s -= acc;
                                }
                                if (!u && !d){
                                    if (s - dec > 0) s -= dec;
                                    else if (s + dec < 0) s += dec;
                                    else s = 0;
                                }
                                if (r && s!=0)  a += turns * s/maxs;
                                if (l && s!=0)   a -= turns * s/maxs;
                                Сatcar[0].tempo = s;
                                Сatcar[0].control = a;
                                for(int i=0;i<N;i++) Сatcar[i].supervision();
                                for(int i=1;i<N;i++) Сatcar[i].object();
                                for(int i=0;i<N;i++)
                                for(int j=0;j<N;j++)
                                {
                                    int dx=0, dy=0;
                                    while (dx*dx+dy*dy<4*R*R)
                                     {
                                       Сatcar[i].x+=dx/10.0;
                                       Сatcar[i].x+=dy/10.0;
                                       Сatcar[j].x-=dx/10.0;
                                       Сatcar[j].y-=dy/10.0;
                                       dx = Сatcar[i].x-Сatcar[j].x;
                                       dy = Сatcar[i].y-Сatcar[j].y;
                                       if (!dx && !dy) break;
                                     }
                                }
                                app.clear(Color::White);
                                if (Сatcar[0].x>320) ox = Сatcar[0].x-320;
                                if (Сatcar[0].y>240) oy = Сatcar[0].y-240;
                                sBackground.setPosition(-ox,-oy);
                                app.draw(sBackground);
                                Color colors[10] = {Color::Green, Color::Yellow, Color::Yellow, Color::Yellow, Color::Yellow};
                                for(int i=0;i<N;i++)
                                {
                                  sCat.setPosition(Сatcar[i].x-ox,Сatcar[i].y-oy);
                                  sCat.setRotation(Сatcar[i].control*180/3.14);
                                  sCat.setColor(colors[i]);
                                  app.draw(sCat);
                                }
                                app.display();
                                }
                                return 0;

                        }
                if(ev.type == Event::MouseButtonPressed)
                    if(ev.key.code == Mouse::Left)
                        if(but2.getGlobalBounds().contains(mousepoz.x,mousepoz.y)){
                            but2.setFillColor(Color(255,0,0));
                            RenderWindow app(VideoMode(640, 480), "Map2");
                                app.setFramerateLimit(60);
                                Texture texture1,texture2;
                                texture1.loadFromFile("E:/proba/Carmape/images/map2.png");
                                texture2.loadFromFile("E:/proba/Carmape/images/Catcat.png");
                                texture1.setSmooth(true);
                                texture2.setSmooth(true);
                                Sprite sBackground(texture1), sCat(texture2);
                                sBackground.scale(2,2);
                                sCat.setOrigin(22, 22);
                                float R=22;
                                const int N=5;
                                Сatcar Сatcar[N];
                                for(int i=0;i<N;i++)
                                {
                                  Сatcar[i].x=300+i*50;
                                  Сatcar[i].y=1700+i*80;
                                  Сatcar[i].tempo=7+i;
                                }
                               float s=0,a=0;
                               float maxs=12.0;
                               float acc=0.2, dec=0.3;
                               float turns=0.08;
                               int ox=0,oy=0;
                                while (app.isOpen())
                                {
                                    Event e;
                                    while (app.pollEvent(e))
                                    {
                                        if (e.type == Event::Closed)
                                            app.close();
                                    }
                                bool u=0,r=0,d=0,l=0;
                                if (Keyboard::isKeyPressed(Keyboard::W)) u=1;
                                if (Keyboard::isKeyPressed(Keyboard::D)) r=1;
                                if (Keyboard::isKeyPressed(Keyboard::S)) d=1;
                                if (Keyboard::isKeyPressed(Keyboard::A)) l=1;
                                if (u && s<maxs){
                                    if (s < 0)  s += dec;
                                    else  s += acc;
                                }
                                if (d && s>-maxs){
                                    if (s > 0) s -= dec;
                                    else  s -= acc;
                                }
                                if (!u && !d){
                                    if (s - dec > 0) s -= dec;
                                    else if (s + dec < 0) s += dec;
                                    else s = 0;
                                }
                                if (r && s!=0)  a += turns * s/maxs;
                                if (l && s!=0)   a -= turns * s/maxs;
                                Сatcar[0].tempo = s;
                                Сatcar[0].control = a;
                                for(int i=0;i<N;i++) Сatcar[i].supervision();
                                for(int i=1;i<N;i++) Сatcar[i].object();
                                for(int i=0;i<N;i++)
                                for(int j=0;j<N;j++)
                                {
                                    int dx=0, dy=0;
                                    while (dx*dx+dy*dy<4*R*R)
                                     {
                                       Сatcar[i].x+=dx/10.0;
                                       Сatcar[i].x+=dy/10.0;
                                       Сatcar[j].x-=dx/10.0;
                                       Сatcar[j].y-=dy/10.0;
                                       dx = Сatcar[i].x-Сatcar[j].x;
                                       dy = Сatcar[i].y-Сatcar[j].y;
                                       if (!dx && !dy) break;
                                     }
                                }
                                app.clear(Color::White);
                                if (Сatcar[0].x>320) ox = Сatcar[0].x-320;
                                if (Сatcar[0].y>240) oy = Сatcar[0].y-240;
                                sBackground.setPosition(-ox,-oy);
                                app.draw(sBackground);
                                Color colors[10] = {Color::Blue, Color::Yellow, Color::Yellow, Color::Yellow, Color::Yellow};
                                for(int i=0;i<N;i++)
                                {
                                  sCat.setPosition(Сatcar[i].x-ox,Сatcar[i].y-oy);
                                  sCat.setRotation(Сatcar[i].control*180/3.14);
                                  sCat.setColor(colors[i]);
                                  app.draw(sCat);
                                }
                                app.display();
                                }
                                return 0;

                        }
                if(ev.type == Event::MouseButtonPressed)
                    if(ev.key.code == Mouse::Left)
                        if(but3.getGlobalBounds().contains(mousepoz.x,mousepoz.y)){
                            but3.setFillColor(Color(255,0,0));
                            RenderWindow app(VideoMode(640, 480), "Map3");
                                app.setFramerateLimit(60);
                                Texture texture1,texture2;
                                texture1.loadFromFile("E:/proba/Carmape/images/map3.png");
                                texture2.loadFromFile("E:/proba/Carmape/images/Catcat.png");
                                texture1.setSmooth(true);
                                texture2.setSmooth(true);
                                Sprite sBackground(texture1), sCat(texture2);
                                sBackground.scale(2,2);
                                sCat.setOrigin(22, 22);
                                float R=22;
                                const int N=5;
                                Сatcar Сatcar[N];
                                for(int i=0;i<N;i++)
                                {
                                  Сatcar[i].x=300+i*50;
                                  Сatcar[i].y=1700+i*80;
                                  Сatcar[i].tempo=7+i;
                                }
                               float s=0,a=0;
                               float maxs=12.0;
                               float acc=0.2, dec=0.3;
                               float turns=0.08;
                               int ox=0,oy=0;
                                while (app.isOpen())
                                {
                                    Event e;
                                    while (app.pollEvent(e))
                                    {
                                        if (e.type == Event::Closed)
                                            app.close();
                                    }
                                bool u=0,r=0,d=0,l=0;
                                if (Keyboard::isKeyPressed(Keyboard::W)) u=1;
                                if (Keyboard::isKeyPressed(Keyboard::D)) r=1;
                                if (Keyboard::isKeyPressed(Keyboard::S)) d=1;
                                if (Keyboard::isKeyPressed(Keyboard::A)) l=1;
                                if (u && s<maxs){
                                    if (s < 0)  s += dec;
                                    else  s += acc;
                                }
                                if (d && s>-maxs){
                                    if (s > 0) s -= dec;
                                    else  s -= acc;
                                }
                                if (!u && !d){
                                    if (s - dec > 0) s -= dec;
                                    else if (s + dec < 0) s += dec;
                                    else s = 0;
                                }
                                if (r && s!=0)  a += turns * s/maxs;
                                if (l && s!=0)   a -= turns * s/maxs;
                                Сatcar[0].tempo = s;
                                Сatcar[0].control = a;
                                for(int i=0;i<N;i++) Сatcar[i].supervision();
                                for(int i=1;i<N;i++) Сatcar[i].object();
                                for(int i=0;i<N;i++)
                                for(int j=0;j<N;j++)
                                {
                                    int dx=0, dy=0;
                                    while (dx*dx+dy*dy<4*R*R)
                                     {
                                       Сatcar[i].x+=dx/10.0;
                                       Сatcar[i].x+=dy/10.0;
                                       Сatcar[j].x-=dx/10.0;
                                       Сatcar[j].y-=dy/10.0;
                                       dx = Сatcar[i].x-Сatcar[j].x;
                                       dy = Сatcar[i].y-Сatcar[j].y;
                                       if (!dx && !dy) break;
                                     }
                                }
                                app.clear(Color::White);
                                if (Сatcar[0].x>320) ox = Сatcar[0].x-320;
                                if (Сatcar[0].y>240) oy = Сatcar[0].y-240;
                                sBackground.setPosition(-ox,-oy);
                                app.draw(sBackground);
                                Color colors[10] = {Color::Blue, Color::Yellow, Color::Yellow, Color::Yellow, Color::Yellow};
                                for(int i=0;i<N;i++)
                                {
                                  sCat.setPosition(Сatcar[i].x-ox,Сatcar[i].y-oy);
                                  sCat.setRotation(Сatcar[i].control*180/3.14);
                                  sCat.setColor(colors[i]);
                                  app.draw(sCat);
                                }
                                app.display();
                                }
                                return 0;

                        }

             }
        win.clear(Color::White);
        win.draw(sprite1);
        win.draw(but1);
        win.draw(but2);
        win.draw(but3);
        win.display();

    }
      return 0;
}
//−−−−− •−−−− −−−−− −−−−− −−−−− −−−−− •−−−− •−−−−
//−−−−− •−−−− •−−−− −−−−− •−−−− −−−−− −−−−− •−−−−
//−−−−− •−−−− •−−−− −−−−− −−−−− −−−−− •−−−− •−−−−
//−−−−− •−−−− •−−−− −−−−− −−−−− −−−−− −−−−− •−−−−
//−−−−− •−−−− •−−−− −−−−− −−−−− •−−−− −−−−− −−−−−
//−−−−− •−−−− •−−−− −−−−− −−−−− −−−−− −−−−− •−−−−
//−−−−− −−−−− •−−−− •−−−− −−−−− −−−−− •−−−− •−−−−
//−−−−− −−−−− •−−−− •−−−− −−−−− −−−−− •−−−− •−−−−
//−−−−− −−−−− •−−−− •−−−− −−−−− −−−−− −−−−− •−−−−
//−−−−− −−−−− •−−−− •−−−− −−−−− −−−−− −−−−− −−−−−
