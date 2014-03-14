package fr.univaix.iut.pokebattle.bot;

import twitter4j.*;

import java.util.List;

/**
 * Created by guillaume on 14/03/14.
 */

public class App {
    public static void main(String[] args) throws TwitterException {

        Twitter twitter = TwitterFactory.getSingleton();
        Query query = new Query("@viedemerde");
        query.setCount(10000);
        QueryResult result=twitter.search(query);
        do{
            List<Status> tweets = result.getTweets();
            for(Status tweet: tweets){
                System.out.println("Tweet: "+tweet.getText());
            }
            query=result.nextQuery();
            if(query!=null)
                result=twitter.search(query);
        }while(query!=null);
    }
}
