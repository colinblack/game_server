package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class SetActivity
	{
		public static const PROTO:String = "Admin.SetActivity";
		public var package_root:*;
		public  var message:*;
		public var actId:int;
		public var status:Byte;
		public function SetActivity(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			actId = undefined;
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.actId = this.actId;
			this.status.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetActivity
		{
			actId = undefined;
			status = undefined;
			this.actId = msgObj.actId;
			this.status = new Byte();
			this.status.writeArrayBuffer(msgObj.status);
			this.status.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetActivity
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}