package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CheckNameAvailableReq
	{
		public static const PROTO:String = "ProtoAlliance.CheckNameAvailableReq";
		public var package_root:*;
		public  var message:*;
		public var name:Byte;
		public function CheckNameAvailableReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			this.name.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CheckNameAvailableReq
		{
			name = undefined;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CheckNameAvailableReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}