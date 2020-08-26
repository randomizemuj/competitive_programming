
import java.util.Timer;
import java.util.TimerTask;
public class Main
{
    public static void main(String args[]){
	solution(new Command() {
            @Override
            public void execute() {
                {
                    System.out.println("Hello World");
                }
            }
        }, 1000);

        // java 8
        scheduler_command(() -> System.out.println("Hello World"), 1000);
    }

    public static void scheduler_command(Command command, int n) {
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                command.execute();
            }
        }, n);

    }

    interface Command {
        public void execute();
    }
}
