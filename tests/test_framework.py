import unittest

from trajectory_reconstructor.framework import (
    Observation,
    ObservationPreprocessor,
    PathReconstructor,
    ReconstructedPath,
    TrajectoryFramework,
    TrajectoryTracker,
    TrackedTrajectory,
)


class FakePreprocessor(ObservationPreprocessor):
    def __init__(self):
        self.called = False

    def preprocess(self, observations):
        self.called = True
        return list(observations)


class FakeReconstructor(PathReconstructor):
    def __init__(self):
        self.inputs = None

    def reconstruct(self, observations):
        self.inputs = list(observations)
        return ReconstructedPath(points=self.inputs)


class FakeTracker(TrajectoryTracker):
    def __init__(self):
        self.inputs = None

    def track(self, path):
        self.inputs = path
        return TrackedTrajectory(path=path, track_id="demo-track")


class FrameworkTests(unittest.TestCase):
    def test_framework_runs_pipeline_in_order(self):
        preprocessor = FakePreprocessor()
        reconstructor = FakeReconstructor()
        tracker = FakeTracker()
        framework = TrajectoryFramework(preprocessor, reconstructor, tracker)

        observations = [
            Observation(timestamp=1.0, x=0.1, y=0.2),
            Observation(timestamp=2.0, x=0.2, y=0.4),
        ]

        result = framework.run(observations)

        self.assertTrue(preprocessor.called)
        self.assertEqual(reconstructor.inputs, observations)
        self.assertEqual(tracker.inputs.points, observations)
        self.assertEqual(result.track_id, "demo-track")


if __name__ == "__main__":
    unittest.main()
