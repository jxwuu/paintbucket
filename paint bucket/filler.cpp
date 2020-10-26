/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"
#include <iostream>

using namespace std; 

/**
 * STRIPE is given as an example
*/
animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, scp, tolerance, frameFreq);
}
animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{

    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, scp, tolerance, frameFreq);
}



/**
 * @todo your turn!
 */

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */

    borderColorPicker bb(borderColor, img, tolerance, *(img.getPixel(x,y)) ); 
    return fill<Stack>(img, x, y, bb, tolerance, frameFreq);
}

/* Given implementation of a DFS conwa fill. */
/*where is the error haaa . .. :"( */
animation filler::fillConwayDFS(PNG& img, int x, int y, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    conwayColorPicker bb;
    return fill<Stack>(img, x, y, bb, tolerance, frameFreq);
}
animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */

    gridColorPicker bb(fillColor, spacing); 
    return fill<Queue>(img, x, y, bb, tolerance, frameFreq);
}
animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    gridColorPicker bb(fillColor, spacing); 
    return fill<Stack>(img, x, y, bb, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     */
    borderColorPicker bb(borderColor, img, tolerance, *(img.getPixel(x,y))); 
    return fill<Queue>(img, x, y, bb, tolerance, frameFreq);
}

/* Given implementation of a BFS conwa fill. */
animation filler::fillConwayBFS(PNG& img, int x, int y, double tolerance, int frameFreq)
{    /**
     * @todo Your code here! You should replace the following line with a
     */
    conwayColorPicker bb;
    return fill<Queue>(img, x, y, bb, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     * NOTE: this'll be a long one!
     */
     // breadth-first-search = queue 
     // depth-first-search = stack 

     // place point in structure -> mark as processed 
     // change color when point added to structure 

     // while (!empty) 
     // remove point from structure 
     // -> add unprocessed neighbours to sturcture if color values <= tolerance distance from 
     // center 
     // use colopicker to set new color of pt
     // makr pt as processed
     // if appropriate frame, send current PNG to animation 

     // each pixel has 4 neighbours
     // order you put onto ordering structure
     // >>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
     // up = - dir, down = + dir

     // evry k pixels filled -> add frame to the animation , where k = framefreq 
     
     // leave function, send one last frame to animation 
     // --> final result of fill -> one that is tested 
   

animation result;
int i = 0;
HSLAPixel point = *(img.getPixel(x,y));
int ** s = new int* [img.width()];
OrderingStructure<int> track;

for (unsigned i = 0; i < img.width(); i++ ) {
    s[i] = new int[img.height()];
}

for (unsigned i = 0; i < img.width(); i++) {
    for (unsigned j = 0 ; j < img.height(); j++) {
        s[i][j] = 0;
    }
}

*(img.getPixel(x,y)) = fillColor(x,y);
s[x][y] = 1;
track.add(x*img.height() + y);
i++;

while (!track.isEmpty()) {
    int loc = track.remove();
    int ypt = loc % img.height();
    int xpt = (loc - ypt) / img.height();
    int xshift[] = {0,1,0,-1};
    int yshift[] = {1,0,-1,0};

    for (int k= 0; k < 4; k++) {
        int currX = xpt + xshift[k];
        int currY = ypt + yshift[k];
        if (currX >= 0 && currX < (int)img.width() && 
            currY >= 0 && currY < (int)img.height() && 
            s[currX][currY] == 0 &&
            point.dist(*(img.getPixel(currX,currY))) <= tolerance)  {
            s[currX][currY] = 1;
            track.add(currX*img.height()+ currY);
            *(img.getPixel(currX,currY)) = fillColor(currX,currY);
            i ++;
            if (i % frameFreq == 0) {
                result.addFrame(img);
            }
        }
    }
}
    result.addFrame(img);
    for (unsigned j = 0; j < img.width() ; j ++) {
        delete[] s[j];
    }
    delete[] s;
    return result;
}


    /** FOR ABOVE fill
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a QUEUE, for a depth-first-search, that
     * structure is a STACK.
     * To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 4 neighbors, consisting of 
     *        the 4 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 4 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: 
     *          >>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */



