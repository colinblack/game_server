package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AidInfoCPP
	{
		public static const PROTO:String = "ProtoAlliance.AidInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var name:Byte;
		public function AidInfoCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			this.name.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AidInfoCPP
		{
			uid = undefined;
			name = undefined;
			this.uid = msgObj.uid;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AidInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}