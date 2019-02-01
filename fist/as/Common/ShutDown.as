package com.sanguo.game.server.connectlogic.common.message.Common
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ShutDown
	{
		public static const PROTO:String = "Common.ShutDown";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var sign:String;
		public function ShutDown(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ts = undefined;
			sign = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.sign = this.sign;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShutDown
		{
			ts = undefined;
			sign = undefined;
			this.ts = msgObj.ts;
			this.sign = msgObj.sign;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShutDown
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}