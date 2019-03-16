#pragma once

#include "CV/ConvexityDefectExtractor.h"

namespace HoloHands
{
   class HandDetector
   {
   public:
      HandDetector();
      void Process(cv::Mat& input);

      void IsClosed(bool isClosed) { _isClosedHand = isClosed; }
      cv::Mat& GetDebugImage() { return _debugImage; }
      cv::Point GetHandPosition() { return _handPosition; }
      cv::Point GetHandCenter() { return _handCenter; }
      void ShowDebugInfo(bool enabled);

   private:
      const double MAX_IMAGE_DEPTH = 1000;
      const double MIN_CONTOUR_SIZE = 10;

      ConvexityDefectExtractor _defectExtractor;
      bool _isClosedHand;
      cv::Point _handPosition;
      cv::Point _leftDirection;
      cv::Point _handCenter;
      std::vector<cv::Point> _contour;
      cv::Mat _debugImage;
      bool _showDebugInfo;

      void ProcessOpenHand();
      void ProcessClosedHand();

      static void CalculateBounds(
         const std::vector<std::vector<cv::Point>>& contours,
         std::vector<cv::Rect>& bounds);

      static bool Intersects(
         const cv::Rect& a,
         const cv::Rect& b);

      void FilterContour(
         const std::vector<cv::Point>& newContour,
         const cv::Rect& newBounds,
         std::vector<std::vector<cv::Point>>& filteredContours,
         std::vector<cv::Rect>& filteredBounds);

      void FilterContours(
         const std::vector<std::vector<cv::Point>>& rawCountours,
         const std::vector<cv::Rect>& rawBounds,
         std::vector<std::vector<cv::Point>>& filteredContours,
         std::vector<cv::Rect>& filteredBounds);

      int FindLargestContour(
         const std::vector<std::vector<cv::Point>>& contours,
         const std::vector<cv::Rect>& bounds);

      void CalculateHandPosition(
         const std::vector<cv::Point>& contour,
         cv::Point& position,
         cv::Point& direction);
   };
}