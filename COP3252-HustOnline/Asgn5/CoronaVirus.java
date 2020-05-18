import java.util.Random;
public class CoronaVirus extends Enemy {


    
  public CoronaVirus() {
    setName("COVID19");
    setHealth(100);
    Random rand = new Random();
      int rand_int1 = rand.nextInt(5);
    setWeapon(rand_int1); // that corona symptom
  }
  @Override public void fight(Knight opp) {
    int damage = opp.getWeaponDamage();

    try {
      takeDamage(damage);
    }
    catch(InvalidDamageException e) {
      setHealth(0);
    }

    System.out.printf("%s attacks the %s with %s and causes %d damage. The %s's health is now %d\n", opp.getName(), getName(), opp.getWeapon() ,damage, getName(), getHealth());
  }

  @Override public String toString() {
    return "an Angry " + getName();
  }
}
