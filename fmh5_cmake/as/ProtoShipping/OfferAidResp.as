package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class OfferAidResp
	{
		public static const PROTO:String = "ProtoShipping.OfferAidResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var selfshipping:ShippingCPP;
		public var othboxes:ShippingBoxCPP;
		public var othboxid:int;
		public function OfferAidResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			selfshipping = undefined;
			othboxes = undefined;
			othboxid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.selfshipping = this.selfshipping.serialize();
			if(this.othboxes!= undefined)
			{
				serializeObj.othboxes = this.othboxes.serialize();
			}
			if(this.othboxid!= undefined)
			{
				serializeObj.othboxid = this.othboxid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferAidResp
		{
			commons = undefined;
			selfshipping = undefined;
			othboxes = undefined;
			othboxid = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.selfshipping = new ShippingCPP(package_root).unserialize(msgObj.selfshipping);
			if(msgObj.hasOwnProperty("othboxes"))
			{
				this.othboxes = new ShippingBoxCPP(package_root).unserialize(msgObj.othboxes);
			}
			if(msgObj.hasOwnProperty("othboxid"))
			{
				this.othboxid = msgObj.othboxid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferAidResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}