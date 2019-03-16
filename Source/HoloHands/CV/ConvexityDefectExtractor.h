#pragma once

namespace HoloHands
{
   struct Defect
   {
      Defect()
         :
         Depth(0)
      {}

      cv::Point Start;
      cv::Point End;
      cv::Point Far;
      cv::Point Mid;
      float Depth;
   };

   class ConvexityDefectExtractor
   {
   public:
      ConvexityDefectExtractor();

      bool FindDefect(
         const std::vector<cv::Point>& contour,
         Defect& outDefect);

      void ShowDebugInfo(bool enabled);

      void SetImageSize(const cv::Size& size);

   private:
      double CalculateDefectScore(const Defect& defect);

      static Defect GetDefectFromContour(
         const std::vector<cv::Point>& contour,
         const cv::Vec4i& defectIndices);

      const double MIN_DEFECT_DEPTH = 20;

      const double HEIGHT_BIAS = 1.0;
      const double DEPTH_BIAS = 0.5;
      const double VERTICALITY_BIAS = 10.0;

      cv::Size _imageSize;
      bool _showDebugInfo;
   };
}