#include <ompl/base/SpaceInformation.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/geometric/SimpleSetup.h>

#include <ompl/config.h>
#include <iostream>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state)
{
    const auto *se3state = state->as<ob::SE3StateSpace::StateType>();

    const auto *pos = se3state->as<ob::RealVectorStateSpace::StateType>(0);

    const auto *rot = se3state->as<ob::SO3StateSpace::StateType>(1);

    return (const void*)rot != (const void*)pos;
}

void plan()
{
    //construct the state space we are planning in
    auto space(std::make_shared<ob::SE3StateSpace>());

    // set the bounds for the R^3 part of SE(3)
    ob::RealVectorBounds bounds(3);
    bounds.setLow(-1);
    bounds.setHigh(1);

    space->setBounds(bounds);

    // Construct an instance of space informatioin from this state space
    auto si(std::make_shared<ob::SpaceInformation>(space));

    si->setStateValidityChecker(isStateValid);

    // Create a random start state
    ob::ScopedState<> start(space);
    start.random();

    // Create a random goal state
    ob::ScopedState<> goal(space);
    goal.random();

    // Create a problem instance
    auto pdef(std::make_shared<ob::ProblemDefinition>(si));

    // Set the start and goal states
    pdef->setStartAndGoalStates(start, goal);

    // Create a planner for the defined space
    auto planner(std::make_shared<og::RRTConnect>(si));

    // Set the problem we art trying to solve for the planner
    planner->setProblemDefinition(pdef);

    // Perform setup steps for the planner
    planner->setup();

    // Print the settings for this space
    si->printSettings(std::cout);

    // Print the problem settings
    pdef->print(std::cout);

    // Attempt to solve the problem within one second of planning time
    ob::PlannerStatus solved = planner->ob::Planner::solve(1.0);

    if(solved)
    {
        ob::PathPtr path = pdef->getSolutionPath();
        std::cout << "Found solution: " << std::endl;
        path->print(std::cout);
    }
    else
        std::cout << "No solution found" << std::endl;
}

void planWithSimpleSetup()
{
    auto space(std::make_shared<ob::SE3StateSpace>());

    ob::RealVectorBounds bounds(3);
    bounds.setLow(-1);
    bounds.setHigh(1);
    space->setBounds(bounds);

    // Define a simple setup class
    og::SimpleSetup ss(space);

    // Set state validity checking for this space
    ss.setStateValidityChecker([](const ob::State *state) { return isStateValid(state); });

    // create a random start state
    ob::ScopedState<> start(space);
    start.random();

    // create a random goal state
    ob::ScopedState<> goal(space);
    goal.random();

    // set the start and goal states
    ss.setStartAndGoalStates(start, goal);

    // this call is optional, but we put it in to get more output information
    ss.setup();
    ss.print();

    // attempt to solve the problem within one second of planning time
    ob::PlannerStatus solved = ss.solve(1.0);

    if (solved)
    {
        std::cout << "Found solution:" << std::endl;
        // print the path to screen
        ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);
    }
    else
        std::cout << "No solution found" << std::endl;
}

int main() {
    std::cout << "OMPL Version is " << OMPL_VERSION << std::endl;
    plan();
    std::cout << std::endl << std::endl;
    planWithSimpleSetup();
    return 0;
}
