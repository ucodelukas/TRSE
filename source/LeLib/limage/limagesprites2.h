#ifndef LIMAGESPRITES2_H
#define LIMAGESPRITES2_H
#include <QKeyEvent>
#include "source/LeLib/limage/multicolorimage.h"

#include "source/LeLib/limage/charsetimage.h"
#include "source/LeLib/util/util.h"
#include "source/LeLib/limage/limagecontainer.h"

class LSprite : public LImageContainerItem {
public:
    int m_pcWidth = 3;
    int m_pcHeight = 3;

    int HEADER_SIZE = 16;
    int HEADER_MULTICOLOR = 0;

    QByteArray m_header;

    QVector<PixelChar> m_data;

    LSprite() {
        m_header.resize(HEADER_SIZE);
    }

    QByteArray ToQByteArray(int mask) override;

    void Clear() override {
        for (PixelChar &pc : m_data)
            pc.Clear(pc.c[0]);
    }

    LSprite(QByteArray& a, int index, int mask) {
        int c = index;
        Init(1,1);
        for (int y=0;y<3;y++) {
            for (int x=0;x<3;x++) {
                for (int j=0;j<8;j++) {
                    int d = c+3*j;
                    m_data[y*3+x].p[j] = PixelChar::reverse(a[d]);
                    m_data[y*3+x].p[j] = m_data[y*3+x].flipSpriteBit(j, mask);
                }
                c++;
            }
            c+=7*3;
        }

    }

    void FillColor(int color, int idx) {
        for (int i=0;i<m_data.count();i++) {
            m_data[i].c[idx] = color;
        }
    }

    void Init(int w, int h) override {
        m_height = w;
        m_width =h;
        m_data.resize(m_height*m_width*m_pcWidth*m_pcHeight);
        m_header.resize(HEADER_SIZE);
    }
    PixelChar* GetSetData(float x, float y, float& ix, float& iy, uchar bitMask);

    void setPixel(float x, float y, uchar color, uchar bitMask);
    uchar getPixel(float x, float y, uchar bitMask);


};


class LImageSprites2 : public CharsetImage, public LImageContainer
{
public:
    LImageSprites2(LColorList::Type t);
//    LImageSprites(LColorList::Type t);

//    LImageSprites2() {}


    LSprite m_copy;



    void ImportBin(QFile& f) override;
    void ExportBin(QFile& f) override;


    void CopyFrom(LImage* mc) override;

    QString GetCurrentDataString() override {
        if (m_current<0) return "";
        QString blockSize = " block size (" +QString::number(m_items[m_current]->m_width);
        blockSize += ", " +QString::number(m_items[m_current]->m_height)+")";
        return "  Sprite : " + QString::number(m_current) + "/" +
                QString::number(m_items.count()) + blockSize;
    }


   void Copy();

   void setPixel(int x, int y, unsigned int color) override;

   unsigned int getPixel(int x, int y) override;

   void SaveBin(QFile& file) override;
   void LoadBin(QFile& file) override;
   void SetColor(uchar col, uchar idx) override;
   void SetColor(uchar col, uchar idx, LSprite& s);

   bool KeyPress(QKeyEvent *e) override;

   void CopyChar() override;
   void PasteChar() override;
   void setMultiColor(bool doSet) override {

   }



   void ToQImage(LColorList& lst, QImage& img, float zoom, QPointF center) override;


   void ToggleSpriteMulticolor();
   void MegaTransform(int flip, int x, int y);

   void AddNew(int w, int h) override;
/*   void Delete() override;

   void Next() override {
       if (m_current<m_sprites.count()-1)  {
           m_current++;
       }
   }

   void Prev() override {
       if (m_current>0)  {
           m_current--;
       }

   }
*/

   virtual void FlipHorizontal() override;
   virtual void FlipVertical() override;
   virtual void Transform(int x, int y) override;
   virtual int getContainerCount() override {return m_items.count();}


   void ShiftSprites(int i);


};

#endif // LIMAGESPRITES2_H
