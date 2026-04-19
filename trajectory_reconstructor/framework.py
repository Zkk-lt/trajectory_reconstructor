from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Iterable, List, Sequence


@dataclass(frozen=True)
class Observation:
    """Single relative perception point."""

    timestamp: float
    x: float
    y: float


@dataclass(frozen=True)
class ReconstructedPath:
    """Path reconstructed from relative observations."""

    points: Sequence[Observation]


@dataclass(frozen=True)
class TrackedTrajectory:
    """Tracking output based on reconstructed path."""

    path: ReconstructedPath
    track_id: str


class ObservationPreprocessor(ABC):
    """Normalizes and filters raw observations."""

    @abstractmethod
    def preprocess(self, observations: Iterable[Observation]) -> Sequence[Observation]:
        raise NotImplementedError


class PathReconstructor(ABC):
    """Builds a coherent path from preprocessed observations."""

    @abstractmethod
    def reconstruct(self, observations: Sequence[Observation]) -> ReconstructedPath:
        raise NotImplementedError


class TrajectoryTracker(ABC):
    """Applies tracking on reconstructed paths."""

    @abstractmethod
    def track(self, path: ReconstructedPath) -> TrackedTrajectory:
        raise NotImplementedError


class TrajectoryFramework:
    """
    Logical algorithm framework:
    1) preprocess observations
    2) reconstruct path
    3) track trajectory
    """

    def __init__(
        self,
        preprocessor: ObservationPreprocessor,
        reconstructor: PathReconstructor,
        tracker: TrajectoryTracker,
    ) -> None:
        self._preprocessor = preprocessor
        self._reconstructor = reconstructor
        self._tracker = tracker

    def run(self, observations: Iterable[Observation]) -> TrackedTrajectory:
        preprocessed_observations: List[Observation] = list(
            self._preprocessor.preprocess(observations)
        )
        reconstructed_path = self._reconstructor.reconstruct(preprocessed_observations)
        return self._tracker.track(reconstructed_path)
