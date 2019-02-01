package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoFriendBattleReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoFriendBattleReq";
		public var package_root:*;
		public  var message:*;
		public var otherId:int;
		public var common:BattleCommon;
		public function ProtoFriendBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			otherId = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.otherId = this.otherId;
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoFriendBattleReq
		{
			otherId = undefined;
			common = undefined;
			this.otherId = msgObj.otherId;
			this.common = new BattleCommon(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoFriendBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}