package tweet.vdm;

import com.sun.java.swing.plaf.motif.resources.motif;
import twitter4j.*;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * Created by guillaume on 14/03/14.
 */

public class App {
    public String GetResult(String cible) throws TwitterException {

        String resulte = "";
        Twitter twitter = TwitterFactory.getSingleton();
        Query query = new Query(cible);
        int numberOfTweets = 10000;
        long lastID = Long.MAX_VALUE;
        ArrayList<Status> tweets = new ArrayList<Status>();
        while (tweets.size () < numberOfTweets) {
            if (numberOfTweets - tweets.size() > 100)
                query.setCount(100);
            else
                query.setCount(numberOfTweets - tweets.size());
                QueryResult result = twitter.search(query);
                tweets.addAll(result.getTweets());
                for (Status t: tweets)
                    if(t.getId() < lastID) lastID = t.getId();
            query.setMaxId(lastID-1);
        }

        for(Status tweet: tweets){
            String message = tweet.getText();
            resulte += "\"" + tweet.getCreatedAt() + "\"" + ";"
                    + "\"" + "@" + tweet.getUser().getScreenName() + "\"" + ";"+ "\"";
                    for(int i = 0; i < message.length(); ++i)
                    {
                        if(message.charAt(i) != ' ' && message.charAt(i) != '\n')
                            resulte += message.charAt(i);
                        else resulte += "\"" +";" + "\"" ;
                    }
                    resulte += "\"" + '\n';
        }
        return resulte;
    }

        public void CreateFile() throws TwitterException {
        try {
            FileWriter fw = new FileWriter("resources.csv") ;
            BufferedWriter bw = new BufferedWriter (fw) ;
            bw.newLine();
            PrintWriter pw = new PrintWriter(bw) ;
            pw.print(GetResult("#linux"));
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