package apriori;

/**
 * Created by guillaume on 19/03/14.
 */
public class Element {
    int oldid;
    int id = 0;
    public Element(int iold, int inew){
        if(inew < 0) inew = 0;
        oldid = iold;
        id = inew;
    }

    boolean operator<(Element e)
    {
        return oldid < e.oldid;
    }
}
