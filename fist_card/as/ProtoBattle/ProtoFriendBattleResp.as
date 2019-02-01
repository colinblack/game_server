package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoFriendBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoFriendBattleResp";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var common:ProtoBattleCPP;
		public function ProtoFriendBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoFriendBattleResp
		{
			battleid = undefined;
			common = undefined;
			this.battleid = msgObj.battleid;
			this.common = new ProtoBattleCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoFriendBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}