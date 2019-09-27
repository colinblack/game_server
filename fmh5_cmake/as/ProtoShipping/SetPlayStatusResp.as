package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class SetPlayStatusResp
	{
		public static const PROTO:String = "ProtoShipping.SetPlayStatusResp";
		public var package_root:*;
		public  var message:*;
		public var shipping:ShippingCPP;
		public function SetPlayStatusResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shipping = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shipping = this.shipping.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetPlayStatusResp
		{
			shipping = undefined;
			this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetPlayStatusResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}