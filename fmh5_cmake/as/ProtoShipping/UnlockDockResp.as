package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class UnlockDockResp
	{
		public static const PROTO:String = "ProtoShipping.UnlockDockResp";
		public var package_root:*;
		public  var message:*;
		public var shipping:ShippingCPP;
		public var commons:CommonItemsCPP;
		public function UnlockDockResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shipping = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shipping = this.shipping.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockDockResp
		{
			shipping = undefined;
			commons = undefined;
			this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockDockResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}