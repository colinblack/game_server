package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class GetAllFriendsResp
	{
		public static const PROTO:String = "ProtoFriend.GetAllFriendsResp";
		public var package_root:*;
		public  var message:*;
		public var concerns:Vector.<ConcernFolkCPP>;
		public var fans:Vector.<FansCPP>;
		public var helpers:Vector.<FolkCPP>;
		public function GetAllFriendsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			concerns = new Vector.<ConcernFolkCPP>();
			fans = new Vector.<FansCPP>();
			helpers = new Vector.<FolkCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.concerns = [];
			for(var i:int = 0;i < this.concerns.length;i++)
			{
				serializeObj.concerns.push(this.concerns[i].serialize());
			}
			serializeObj.fans = [];
			for(var i:int = 0;i < this.fans.length;i++)
			{
				serializeObj.fans.push(this.fans[i].serialize());
			}
			serializeObj.helpers = [];
			for(var i:int = 0;i < this.helpers.length;i++)
			{
				serializeObj.helpers.push(this.helpers[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetAllFriendsResp
		{
			concerns = new Vector.<ConcernFolkCPP>();
			fans = new Vector.<FansCPP>();
			helpers = new Vector.<FolkCPP>();
			for(var i:int = 0;i < msgObj.concerns.length;i++)
			{
				this.concerns.push(new ConcernFolkCPP(package_root).unserialize(msgObj.concerns[i]));
			}
			for(var i:int = 0;i < msgObj.fans.length;i++)
			{
				this.fans.push(new FansCPP(package_root).unserialize(msgObj.fans[i]));
			}
			for(var i:int = 0;i < msgObj.helpers.length;i++)
			{
				this.helpers.push(new FolkCPP(package_root).unserialize(msgObj.helpers[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetAllFriendsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}