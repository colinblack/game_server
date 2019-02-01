package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoMartialClubBattleReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoMartialClubBattleReq";
		public var package_root:*;
		public  var message:*;
		public var myMartialGrade:int;
		public var othUid:int;
		public var othMartialGrade:int;
		public var common:BattleCommon;
		public function ProtoMartialClubBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myMartialGrade = undefined;
			othUid = undefined;
			othMartialGrade = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myMartialGrade = this.myMartialGrade;
			serializeObj.othUid = this.othUid;
			serializeObj.othMartialGrade = this.othMartialGrade;
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoMartialClubBattleReq
		{
			myMartialGrade = undefined;
			othUid = undefined;
			othMartialGrade = undefined;
			common = undefined;
			this.myMartialGrade = msgObj.myMartialGrade;
			this.othUid = msgObj.othUid;
			this.othMartialGrade = msgObj.othMartialGrade;
			this.common = new BattleCommon(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoMartialClubBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}