package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetDrawRewardReq
	{
		public static const PROTO:String = "User.GetDrawRewardReq";
		public var package_root:*;
		public  var message:*;
		public var free:int;
		public function GetDrawRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			free = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.free = this.free;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetDrawRewardReq
		{
			free = undefined;
			this.free = msgObj.free;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetDrawRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}