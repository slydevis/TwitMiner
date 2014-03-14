package fr.univaix.iut.pokebattle.bot;

import twitter4j.*;

import java.util.List;

/**
 * Created by guillaume on 14/03/14.
 */

public class App {
	
	public static void main(String[] args) throws TwitterException {

        Twitter twitter = TwitterFactory.getSingleton();
        System.out.println(twitter.getAPIConfiguration());
        Query query = new Query("@viedemerde");
        query.setCount(10000);
        QueryResult result=twitter.search(query);
        List<Status> tweets = null;
        do{
            tweets = result.getTweets();
            for(Status tweet: tweets){
                System.out.println("\"" + tweet.getCreatedAt() + ";" + tweet.getUser().getName() + ":" + tweet.getText().replace(' ', ';') + "\"");
            }
            query=result.nextQuery();
            if(query!=null)
                result=twitter.search(query);
        }while(query!=null);
    }
}
