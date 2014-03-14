package fr.univaix.iut.pokebattle.bot;

import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;

import java.util.List;

/**
 * Created by guillaume on 14/03/14.
 */

public class App {
    public static void main(String[] args) throws TwitterException {
        Twitter twitter = TwitterFactory.getSingleton();
        System.out.println(twitter.getAPIConfiguration());
        List<Status> statuses = twitter.getUserTimeline("@viedemerde");
        System.out.println("Showing home timeline.");
        for (Status status : statuses) {
            System.out.println(status.getUser().getName() + ":" +
                    status.getText() + " " + status.getCreatedAt());
        }
    }
}
