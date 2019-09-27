package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class SeekAidResp
	{
		public static const PROTO:String = "ProtoShipping.SeekAidResp";
		public var package_root:*;
		public  var message:*;
		public var shipping:ShippingCPP;
		public var boxes:ShippingBoxCPP;
		public function SeekAidResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shipping = undefined;
			boxes = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shipping = this.shipping.serialize();
			serializeObj.boxes = this.boxes.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):SeekAidResp
		{
			shipping = undefined;
			boxes = undefined;
			this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			this.boxes = new ShippingBoxCPP(package_root).unserialize(msgObj.boxes);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SeekAidResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}