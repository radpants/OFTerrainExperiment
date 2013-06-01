// cache.h
//
// Copyright (C) 2003, 2004 Jason Bevins
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//

#ifndef NOISE_MODULE_CACHE_H
#define NOISE_MODULE_CACHE_H

#include "modulebase.h"

namespace noise
{

  namespace module
  {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @defgroup miscmodules Miscellaneous Modules
    /// @addtogroup miscmodules
    /// @{

    /// Noise module that caches the last output value generated by a source
    /// module.
    ///
    /// If an application passes an input value to the GetValue() method that
    /// differs from the previously passed-in input value, this noise module
    /// instructs the source module to calculate the output value.  This
    /// value, as well as the ( @a x, @a y, @a z ) coordinates of the input
    /// value, are stored (cached) in this noise module.
    ///
    /// If the application passes an input value to the GetValue() method
    /// that is equal to the previously passed-in input value, this noise
    /// module returns the cached output value without having the source
    /// module recalculate the output value.
    ///
    /// If an application passes a new source module to the SetSourceModule()
    /// method, the cache is invalidated.
    ///
    /// Caching a noise module is useful if it is used as a source module for
    /// multiple noise modules.  If a source module is not cached, the source
    /// module will redundantly calculate the same output value once for each
    /// noise module in which it is included.
    ///
    /// This noise module requires one source module.
    class Cache: public Module
    {

      public:

        /// Constructor.
        Cache ();

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        virtual void SetSourceModule (int index, const Module& sourceModule)
        {
          Module::SetSourceModule (index, sourceModule);
          m_isCached = false;
        }

      protected:

        /// The cached output value at the cached input value.
        mutable double m_cachedValue;

        /// Determines if a cached output value is stored in this noise
        /// module.
        mutable double m_isCached;

        /// @a x coordinate of the cached input value.
        mutable double m_xCache;

        /// @a y coordinate of the cached input value.
        mutable double m_yCache;

        /// @a z coordinate of the cached input value.
        mutable double m_zCache;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
