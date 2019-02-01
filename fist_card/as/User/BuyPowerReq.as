package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BuyPowerReq
	{
		public static const PROTO:String = "User.BuyPowerReq";
		public var package_root:*;
		public  var message:*;
		public var propid:int;
		public var ts:int;
		public function BuyPowerReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			propid = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propid = this.propid;
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyPowerReq
		{
			propid = undefined;
			ts = undefined;
			this.propid = msgObj.propid;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyPowerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}