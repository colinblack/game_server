package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class SetFormationResp
	{
		public static const PROTO:String = "ProtoBattle.SetFormationResp";
		public var package_root:*;
		public  var message:*;
		public function SetFormationResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetFormationResp
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetFormationResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}