package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class SetForbidTS
	{
		public static const PROTO:String = "Admin.SetForbidTS";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var forbidts:int;
		public var reason:Byte;
		public function SetForbidTS(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			forbidts = undefined;
			reason = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.forbidts = this.forbidts;
			this.reason.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetForbidTS
		{
			uid = undefined;
			forbidts = undefined;
			reason = undefined;
			this.uid = msgObj.uid;
			this.forbidts = msgObj.forbidts;
			this.reason = new Byte();
			this.reason.writeArrayBuffer(msgObj.reason);
			this.reason.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetForbidTS
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}