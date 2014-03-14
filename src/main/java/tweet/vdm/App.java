package tweet.vdm;

import twitter4j.*;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/**
 * Created by guillaume on 14/03/14.
 */

public class App {
    public String GetResult() throws TwitterException {
        String resulte ="";
        Twitter twitter = TwitterFactory.getSingleton();
        Query query = new Query("@viedemerde");
        query.setCount(10000);
        QueryResult result=twitter.search(query);
        List<Status> tweets;
        do{
            tweets = result.getTweets();
            for(Status tweet: tweets){
                resulte += "Tweet: "+ tweet.getCreatedAt() + ";" + tweet.getUser().getName() + ":" + 
                		((tweet.getText().replace(' ', ';')).replace('é', 'e')).replace('è', 'e') + "\"" + '\n';
            }
            query=result.nextQuery();
            if(query!=null)
                result=twitter.search(query);
        } while(query!=null);
        return resulte;
    }

    public void CreateFile() throws TwitterException {
        try {
            FileWriter fw = new FileWriter("resources.csv") ;
            BufferedWriter bw = new BufferedWriter (fw) ;
            bw.newLine();
            PrintWriter pw = new PrintWriter(bw) ;
            pw.print(GetResult()) ;
            pw.close();
        }
        catch ( IOException e ) {
            System.out.println ( " Problème à l’écriture du fichier " ) ;
            System.exit(0);
        }
    }
    public static void main(String[] args) throws TwitterException {
        App app = new App();
        app.CreateFile();
    }
}