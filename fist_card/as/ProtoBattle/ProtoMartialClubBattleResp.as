package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoMartialClubBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoMartialClubBattleResp";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var common:ProtoBattleCPP;
		public function ProtoMartialClubBattleResp(root:*)
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
		public function unserialize(msgObj:*):ProtoMartialClubBattleResp
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
		public function decode(buffer:*):ProtoMartialClubBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}