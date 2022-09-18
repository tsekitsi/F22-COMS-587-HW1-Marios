import java.util.Set;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class AgentMonitor extends Thread {
    public int CHECK_EVERY_X_SECS = 10;
    public Set<String> agents;
    public ScheduledExecutorService doctor;

    public Runnable healthCheck;
    public AgentMonitor(Set<String> activeAgents) {
        agents = activeAgents;
        healthCheck = new Runnable() {
            public void run() {
                System.out.println("Hello");
            }
        };
        doctor = Executors.newScheduledThreadPool(1);
        doctor.scheduleAtFixedRate(healthCheck, CHECK_EVERY_X_SECS, CHECK_EVERY_X_SECS, TimeUnit.SECONDS);
    }

    /**
     * Add an agent's ID to the set of active agents.
     *
     * @param agentID the unique identifier of the agent to add
     * @return true if the agent was added successfully
     */
    public boolean addAgent(String agentID) {
        return agents.add(agentID);
    }

    /**
     * Remove an agent's ID from the set of active agents.
     *
     * @param agentID the unique identifier of the agent to remove
     * @return true if the agent was contained in the set of active agents
     */
    public boolean removeAgent(String agentID) {
        return agents.remove(agentID);
    }
}
