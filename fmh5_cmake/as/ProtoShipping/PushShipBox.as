package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class PushShipBox
	{
		public static const PROTO:String = "ProtoShipping.PushShipBox";
		public var package_root:*;
		public  var message:*;
		public var box:ShippingBoxCPP;
		public function PushShipBox(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			box = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.box = this.box.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushShipBox
		{
			box = undefined;
			this.box = new ShippingBoxCPP(package_root).unserialize(msgObj.box);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushShipBox
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}